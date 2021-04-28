int printSerial(int** arr){
    char str[100];
    char types[6][12] = {"Add", "Multiply", "Divide", "Squareroot", "Sin", "Cos"};

    /* Make an array of strings */
    sprintf(str, "%11s %11s %11s %11s %11s %11s %11s", " ", "Add", "Multiply", "Divide", "Squareroot", "Sin", "Cos");
    
    /* Send this string across serial */
    Init_out_SCI0(str);
    
    for(int i=0; i < 4; i++){
        sprintf(str, "%11s %11d %11d %11d %11d %11d %11d", types[i], arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5]);
        Init_out_SCI0(str);
    }
}
