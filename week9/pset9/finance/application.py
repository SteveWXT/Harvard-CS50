import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

    stocks = []
    total = 0
    for index, row in enumerate(rows):
        result = lookup(row["symbol"])
        stocks.append(list([row["symbol"], result["name"], row["amount"], result["price"], round(row["amount"]*result["price"], 2)]))
        total += stocks[-1][4]
    total += cash
    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        result = lookup(request.form.get("symbol"))
        if not result:
            return apology("The stock doesn't exist!")

        symbol = result["symbol"]

        shares = int(request.form.get("shares"))
        if shares < 0:
            return apology("The share should be a positive number!")


        cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id = session["user_id"])[0]['cash']
        price = result['price']
        left = cash - shares * float(price)

        if left < 0:
            return apology("You don't have enough money!")

        stock = db.execute("SELECT * from stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=request.form.get("symbol"))
        if not stock:
            db.execute("INSERT INTO stocks(user_id, symbol, amount) VALUES (:user_id, :symbol, :amount)", user_id=session["user_id"], symbol=symbol, amount=shares)
        else:
            amount = stock[0]["amount"] + shares
            db.execute("UPDATE stocks SET amount=:amount WHERE user_id =:user_id AND symbol=:symbol", amount=amount, user_id=session["user_id"], symbol=symbol)


        db.execute("UPDATE users SET cash=:cash WHERE id = :user_id", cash=left, user_id=session["user_id"])
        db.execute("INSERT INTO transactions(user_id, symbol, amount, value) VALUES (:user_id, :symbol, :amount, :value)",
            user_id=session["user_id"], symbol=symbol, amount=shares, value=round(shares * float(price), 2))

        return redirect("/")
    else:
        return render_template("buy.html")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id = session["user_id"])
    history = []
    for row in rows:
        history.append(list((row["symbol"], row["date"], row["amount"], row["value"])))

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Can not find this stock!")
        return render_template("quote.html", stock = stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "GET":
        return render_template("register.html")
    else:
        if not request.form.get("username"):
            return apology("Must input username!")
        elif not request.form.get("password"):
            return apology("Must input password!")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match!")
        elif db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")):
            return apology("User already exists!")
        else:
            db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash=generate_password_hash(request.form.get("password")))


        return redirect("/")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("sell_stock")
        amount = int(request.form.get("sell_amount"))
        price = lookup(symbol)["price"]
        value = round(float(amount) * price , 2)

        cur_amount = db.execute("SELECT * from stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=symbol)[0]["amount"]

        if amount > cur_amount:
            return apology("You don't have enough stock!")
        elif amount == cur_amount:
            db.execute("DELETE FROM stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=symbol)
        else:
            db.execute("UPDATE stocks SET amount = :amount WHERE user_id=:user_id AND symbol=:symbol", amount = cur_amount-amount, user_id=session["user_id"], symbol=symbol)


        cur_cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id = session["user_id"])[0]['cash']
        db.execute("UPDATE users SET cash=:cash WHERE id=:user_id", cash = round(cur_cash + value, 2), user_id=session["user_id"])

        db.execute("INSERT INTO transactions(user_id, symbol, amount, value) VALUES (:user, :symbol, :amount, :value)", user=session["user_id"], symbol=symbol, amount=-amount, value=value)

        return redirect("/")

    else:
        rows = db.execute("SELECT * FROM stocks WHERE user_id=:user_id", user_id = session["user_id"])
        stocks = {}
        for row in rows:
            stocks[row["symbol"]] = row["amount"]

        return render_template("sell.html", stocks = stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
