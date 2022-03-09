#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //look for a candidate called name
    for (int current_candidate = 0; current_candidate < candidate_count; current_candidate++)
    {
        if (strcmp(name, candidates[current_candidate].name) == 0)
        {
            preferences[voter][rank] = current_candidate;
            return true;
            // if candidate is found update preferences so that they are the voters rank preferences
        }
    }
    //if no candidate found, dont update preferences and return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    
    //look at voters preferences and compute the current vote total
    for (int i = 0; i < voter_count ; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (candidates[candidate_index].eliminated == false)
            {
                //looking at each voters top choice that hasnt been eliminated
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        //go through the total votes of each candidate
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
        //if any candidates vote count >= voter_count / 2 
        //print that candidate
        //return true
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min_vote = MAX_VOTERS;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && min_vote > candidates[i].votes)
        {
            min_vote = candidates[i].votes;
        }
    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tie = 0;
    int new_candidate_count = 0;
    
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == true)
        {
            new_candidate_count++;
        }
    }
    
    new_candidate_count = candidate_count - new_candidate_count;
    
    for (int i = 0; i < new_candidate_count; i++)
    {
        if (candidates[i].eliminated == false && min == candidates[i].votes)
        {
            tie++;
        }
        if (tie == new_candidate_count)
        {
            return true;
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (min >= candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
