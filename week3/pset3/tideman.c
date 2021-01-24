#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);

void sort_pairs(void);
void merge_sort(pair temp[]);
void divide(int left, int right, pair temp[]);
void merge(int left, int mid, int right, pair temp[]);

void lock_pairs(void);
bool check_cycle(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                pair_count++;
            }
        }
    }


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp[MAX * (MAX - 1) / 2];

    merge_sort(temp);

    return;
}

//use merge sort
void merge_sort(pair temp[])
{
    int left = 0;
    int right = pair_count - 1;

    divide(left, right, temp);
}

//one step of merge sort using recursion
void divide(int left, int right, pair temp[])
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        //left
        divide(left, mid, temp);
        //right
        divide(mid + 1, right, temp);
        //merge left part and right part
        merge(left, mid, right, temp);
    }

}

void merge(int left, int mid, int right, pair temp[])
{
    int i = left;
    int j = mid + 1;

    int count = 0;

    while (i <= mid && j <= right)
    {
        int strength_left = preferences[pairs[i].winner][pairs[i].loser];
        int strength_right = preferences[pairs[j].winner][pairs[j].loser];

        if (strength_left > strength_right)
        {
            temp[count++] = pairs[i++];
        }
        else
        {
            temp[count++] = pairs[j++];
        }
    }

    //the rest of left
    while (i<=mid)
    {
        temp[count++] = pairs[i++];
    }

    //the rest of right
    while (j<=right)
    {
        temp[count++] = pairs[j++];
    }

    for (int t = 0; left <= right; t++, left++)
    {
        pairs[left] = temp[t];
    }
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (check_cycle())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}


//return true if there is a cycle, return false if isn't
bool check_cycle(void)
{
    //size of adjacency matrix
    int size = candidate_count;

    //out[i] is the out-degree of candidate i
    int out[size];
    for (int i = 0; i < size; i++)
    {
        out[i] = 0;
    }

    //in_nodes[i][j] is whether candidate j is a front node of candidate i
    bool in_nodes[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            in_nodes[i][j] = false;
        }
    }

    //calculate the out-dgree and front nodes of all nodes
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (locked[i][j] == true)
            {
                out[i]++;
                in_nodes[j][i] = true;
            }
        }
    }

    //visted[i]: whether node i is visited
    bool visited[size];
    
    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }
    
    int visited_size = 0;
     

    //iterate through the nodes, every iteration finds node with 0 out-degree, store it and minus the out-degree of its front nodes
    while (visited_size < size)
    {
        for (int i = 0; i < size; i++)
        {
            if (out[i] == 0 && visited[i] == false)
            {
                visited[i] = true;
                visited_size++;
    
                for (int j = 0; j < size; j++)
                {
                    if (in_nodes[i][j] == true)
                    {
                        out[j]--;
                    }
                }
                
                break;
            }
            
            if ((i == size-1) && (visited_size != size))
            {
                return true;
            }
        
        }
        
    }
    
    return false;
}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;

        for (int j = 0; j < candidate_count; j++){
            if (locked[j][i])
            {
                isWinner = false;
            }
        }

        if (isWinner)
        {
            printf("%s\n", candidates[i]);
            break;
        }

    }


    return;
}

