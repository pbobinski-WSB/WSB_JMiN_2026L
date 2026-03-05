int elevator(int input) {
    switch(input) {
        case 0: return 10;
        case 1: return 20;
        case 2: return 30;
        case 3: return 40;
        case 4: return 50;
        case 5: return 60;
        case 6: return 70;
        default: return -1;
    }
}

int elevator2(int input) {
    switch(input) {
        case 0: return 10;
        case 1: return 0;
        case 2: return 30;
        case 3: return 740;
        case 4: return 50;
        case 5: return 160;
        case 6: return 970;
        default: return -1;
    }
}