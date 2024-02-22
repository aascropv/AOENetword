#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int num = 0;
    while (scanf("%d", &num) != EOF) {
        break;
    }
    int activity[num][4];

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 4; j++)
            scanf("%d", &activity[i][j]);
    }

    int eventMax = 0;
    for (int i = 0; i < num; i++) {
        if (activity[i][2] > eventMax)
            eventMax = activity[i][2];
    }
    //count early & late event
    int earlyE[eventMax+1], lateE[eventMax+1];
    for (int i = 0; i < eventMax + 1; i++) {
        earlyE[i] = -1;
        lateE[i] = -1;
    }
    earlyE[0] = 0;
    lateE[0] = 0;
    for (int i = 0; i < num; i++) {
        if (earlyE[activity[i][2]] < earlyE[activity[i][1]] + activity[i][3])
            earlyE[activity[i][2]] = earlyE[activity[i][1]] + activity[i][3];
    }
    lateE[eventMax] = earlyE[eventMax];
    for (int i = num-1; i >= 0; i--) {
        if (lateE[activity[i][2]] - activity[i][3] < lateE[activity[i][1]] || lateE[activity[i][1]] < 0)
            lateE[activity[i][1]] = lateE[activity[i][2]] - activity[i][3];
    }
    //count early and late
    int early[num+1], late[num+1], deviation[num +1];
    for (int i = 0; i < num+1; i++) {
        early[i] = 0;
        late[i] = 0;
        deviation[i] = 0;
    }
    for (int i = 1; i <= num; i++) {
        early[i] = earlyE[activity[i-1][1]];
        late[i] = lateE[activity[i-1][2]] - activity[i-1][3];
        deviation[i] = late[i] - early[i];
    }
    //print early and late
    for (int i = 1; i < num+1; i++) {
        printf("%d %d %d", i-1, early[i], late[i]);
        printf("\n");
    }
    //print the path
    for (int i = 1; i <= num; i++) {
        if (deviation[i] == 0) {
            if (i != num)
                printf("%d ", i-1);
            else
                printf("%d", i-1);
        }
    }
    return 0;
}
