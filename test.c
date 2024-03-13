void solve_white_cross() {
    for (check1 = 0; check1 < 2; check1++) {
        //case_6--------------------
        defcase();
        //case_1---------------------
        for (int i = 0; i < 4; i++) {
            for (k = 0; k < 9; k++) {
                side1[k] = setside(i, k);
            };
            if (white[2 * i] == 'w' && side1[7] != pref[i]) {
                rotate_clock(pref[i]);
                rotate_clock(pref[i]);
                defcase();
            }
        }
        //case_2-----------------------
        for (j = 0; j < 4; j++) {
            int l = j + 1;
            if (j == 3) {
                l = 0;
            }
            for (k = 0; k < 9; k++) {
                side2[k] = setside(l, k);
                side1[k] = setside(j, k);
            }
            if (side1[5] == 'w') {
                rotate_clock(pref[l]);
                rotate_clock('y');
                rotate_clock(pref[l]);
                rotate_clock(pref[l]);
                rotate_clock(pref[l]);
                temp = j;
                defcase();
                j = temp;
            }
        }
        //case_3................
        case3();
        //case_4................
        for (int i = 0; i < 4; i++) {
            for (k = 0; k < 9; k++) {
                side1[k] = setside(i, k);
            }
            if (side1[7] == 'w') {
                rotate_clock(pref[i]);
                temp1 = i;
                case3();
                i = temp1;
            }
        }
        //case_5................
        for (j = 0; j < 4; j++) {
            int l = j + 1;
            if (j == 3) {
                l = 0;
            }
            for (k = 0; k < 9; k++) {
                side2[k] = setside(l, k);
                side1[k] = setside(j, k);
            }
            if (side1[3] == 'w') {
                rotate_clock(pref[j]);
                rotate_clock(pref[l]);
                rotate_clock('y');
                rotate_clock('y');
                rotate_clock(pref[l]);
                rotate_clock(pref[l]);
                rotate_clock(pref[l]);
                rotate_clock(pref[j]);
                rotate_clock(pref[j]);
                rotate_clock(pref[j]);
                defcase();
            }
        }
    }
}
