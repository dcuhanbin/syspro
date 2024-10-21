
int borrow_book(int* borrowed) {
    int book_num; 
    
    printf("id : ");
    scanf("%d", &book_num);

    if (borrowed[book_num] == 1) {
        printf("false\n");
    }
    else {
        printf("true \n");
        borrowed[book_num] = 1;
    }

    return 0;
}
