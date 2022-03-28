#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    
    for (int current_candidate = 0; current_candidate < candidate_count; current_candidate++)
    {
        if (strcmp(name, candidates[current_candidate].name) == 0)
        {
            candidates[current_candidate].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int current_candidate = 0;
    int top_votes = 0;
    
    
    //define who has how many votes
    while (current_candidate < candidate_count)
    {
        if (top_votes < candidates[current_candidate].votes)
        {
            top_votes = candidates[current_candidate].votes;
        }
        current_candidate++;
    }
    //compare every candidate with the "top_votes" number and print evryone with that number
    for (current_candidate = 0; current_candidate < candidate_count; current_candidate++)
    {
        if (candidates[current_candidate].votes == top_votes)
        {
            printf("%s\n", candidates[current_candidate].name);
        }
    }
    
    //print top_candidate
    return;
}
