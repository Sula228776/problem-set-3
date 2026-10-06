#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9
#define MAX_VOTERS 100

typedef struct
{
    char name[50];
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX];

int preferences[MAX_VOTERS][MAX];

int candidate_count;
int voter_count;

bool vote(int voter, int rank, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int index = preferences[i][j];

            if (!candidates[index].eliminated)
            {
                candidates[index].votes++;
                break;
            }
        }
    }
}

bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated &&
            candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated &&
            candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated &&
            candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated &&
            candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

int main(void)
{
    candidate_count = 3;
    voter_count = 5;

    strcpy(candidates[0].name, "Alice");
    strcpy(candidates[1].name, "Bob");
    strcpy(candidates[2].name, "Charlie");

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    vote(0, 0, "Alice");
    vote(0, 1, "Bob");
    vote(0, 2, "Charlie");

    vote(1, 0, "Bob");
    vote(1, 1, "Alice");
    vote(1, 2, "Charlie");

    vote(2, 0, "Charlie");
    vote(2, 1, "Alice");
    vote(2, 2, "Bob");

    vote(3, 0, "Alice");
    vote(3, 1, "Bob");
    vote(3, 2, "Charlie");

    vote(4, 0, "Bob");
    vote(4, 1, "Alice");
    vote(4, 2, "Charlie");

    tabulate();

    if (!print_winner())
    {
        int min = find_min();

        if (!is_tie(min))
        {
            eliminate(min);

            for (int i = 0; i < candidate_count; i++)
            {
                candidates[i].votes = 0;
            }

            tabulate();
            print_winner();
        }
    }

    return 0;
}