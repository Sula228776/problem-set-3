#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

typedef struct
{
    char name[50];
    int votes;
} candidate;

candidate candidates[MAX];
int candidate_count;

bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void)
{
    int max_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main(void)
{
    candidate_count = 3;

    strcpy(candidates[0].name, "Alice");
    strcpy(candidates[1].name, "Bob");
    strcpy(candidates[2].name, "Charlie");

    candidates[0].votes = 0;
    candidates[1].votes = 0;
    candidates[2].votes = 0;

    vote("Alice");
    vote("Bob");
    vote("Alice");
    vote("Charlie");
    vote("Bob");
    vote("Alice");

    printf("Winner:\n");
    print_winner();

    return 0;
}