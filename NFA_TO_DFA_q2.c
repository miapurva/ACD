/*
*   NAME:           YUTIKA CHANDRASHEKHAR KULWE
*   ROLL NO.:       CED15I017
*   COURSE NAME:    Automata and Compiler Design
*   INPUT:          NFA
*   OUTPUT:         DFA
*   USAGE:          cc NFA_TO_DFA_q2.c -o NFA_TO_DFA
*                   ./NFA_TO_DFA
*/


#include <stdio.h>
#include <string.h>
 
#define STATES  256
#define SYMBOLS 20
 
int N_symbols; 
int NFA_states, DFA_states;
char *NFAtab[STATES][SYMBOLS];
int DFA_table[STATES][SYMBOLS];
 
/*Print state-transition table.*/
void display_DFA(int tab[][SYMBOLS], int nstates, int nsymbols)  
{
    int i, j;
 
    printf("\t\t\t\tSTATE TRANSITION TABLE\n");
 
    /* input symbols: '0', '1', ... */
    printf("\t\t\t\t     | ");

    for (i = 0; i < nsymbols; i++) 
        printf("  %c  ", '0'+i);
 
    printf("\n\t\t\t\t-----+--");
    for (i = 0; i < nsymbols; i++) 
        printf("-----");
    printf("\n");
 
    for (i = 0; i < nstates; i++) {
        printf("\t\t\t\t  %c  | ", 'A'+i);  /* state */
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", 'A'+tab[i][j]);
        printf("\n");
    }
}
 
/*Initialize NFA table.*/
void init_NFA()
{
    NFAtab[0][0] = "12";
    NFAtab[0][1] = "13";
    NFAtab[1][0] = "12";
    NFAtab[1][1] = "13";
    NFAtab[2][0] = "4";
    NFAtab[2][1] = "";
    NFAtab[3][0] = "";
    NFAtab[3][1] = "4";
    NFAtab[4][0] = "4";
    NFAtab[4][1] = "4";
 
    NFA_states = 5;
    DFA_states = 0;
    N_symbols = 2;
}
 
/*String 'b' is merged into 'a' in an alphabetical order.*/
void join_states(char *a, char *b)
{
    char temp[STATES], *c=temp, *d=a;
 
    while (*d && *b) {
        if (*d == *b) {
            *c++ = *d++; b++;
        } else if (*d < *b) {
            *c++ = *d++;
        } else
            *c++ = *b++;
    }
    *c = '\0';
 
    if (*d) strcat(c, d);
    else if (*b) strcat(c, b);
 
    strcpy(a, temp);
}
 
/*Get next-state string for current-state string.*/
void get_next_state(char *nextstates, char *cur_states,
    char *nfa[STATES][SYMBOLS], int n_nfa, int symbol)
{
    int i;
    char temp[STATES];
 
    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++)
        join_states(temp, nfa[cur_states[i]-'0'][symbol]);
    strcpy(nextstates, temp);
}
 
//Making your next state as the current state
int state_position(char *state, char statename[][STATES], int *pn)
{
    int i;
 
    if (!*state) return -1; /* no next state */
 
    for (i = 0; i < *pn; i++)
        if (!strcmp(state, statename[i])) return i;
 
    strcpy(statename[i], state);    /* new state-name */
    return (*pn)++;
}
 
/*
    Convert NFA table to DFA table.
    Return value: number of DFA states.
*/
int NFA_to_DFA(char *nfa[STATES][SYMBOLS], int n_nfa,
    int n_sym, int dfa[][SYMBOLS])
{
    char statename[STATES][STATES];
    int i = 0;  /* current index of DFA */
    int n = 1;  /* number of DFA states */
 
    char nextstate[STATES];
    int j;
 
    strcpy(statename[0], "0");  /* start state */
 
    for (i = 0; i < n; i++) {    /* for each DFA state */
        for (j = 0; j < n_sym; j++) {    /* for each input symbol */
            get_next_state(nextstate, statename[i], nfa, n_nfa, j);
            dfa[i][j] = state_position(nextstate, statename, &n);
        }
    }
 
    return n;   /* number of DFA states */
}
 
void main()
{
    init_NFA();
    printf("\n\t\t\t\tConversion of NFA to DFA\n");
    printf("\t\t\t\t-----------------------------\n\n");
    DFA_states = NFA_to_DFA(NFAtab, NFA_states, N_symbols, DFA_table);
    display_DFA(DFA_table, DFA_states, N_symbols);
    printf("\t\t\t\t-----------------------------\n\n");
}