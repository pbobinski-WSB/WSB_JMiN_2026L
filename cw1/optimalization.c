int multiply(int a, int b) { 
    return a * b; 
}


int sum_to_n(int n) {
    int sum = 0;
    for (int i = 0; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

void useless_calculation(int n) {
    long long sum = 0;
    for(int i=0; i<n; i++) {
        sum += i * i; // Liczymy, ale...
    }
    // ... nigdzie nie używamy 'sum'. Nie ma return, nie ma printf.
}

int ladder(int input) {
    if (input == 0) return 10;
    else if (input == 1) return 20;
    else if (input == 2) return 30;
    else if (input == 3) return 40;
    else if (input == 4) return 50;
    else if (input == 5) return 60;
    else if (input == 6) return 70;
    else return -1;
}

int ladder2(int input) {
    if (input == 0) return 10;
    else if (input == 1) return 20;
    else if (input == 2) return 0;
    else if (input == 3) return 440;
    else if (input == 4) return 150;
    else if (input == 5) return 0;
    else if (input == 6) return 970;
    else return -1;
}

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