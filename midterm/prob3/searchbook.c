int search_book(char(*book_name)[30], char(*auth_name)[30],
    char(*publ_name)[30], int num_total_book) {
    int user_input;
    int i;
    char user_search[30];

    printf("1. bookname \n");
    scanf("%d", &user_input);

    scanf("%s", user_search);

    if (user_input == 1) {
       
        for (i = 0; i < num_total_book; i++) {
            if (compare(book_name[i], user_search)) {
                printf("id : %d // bookname: %s //author : %s // year : %s \n", i,
                    book_name[i], auth_name[i], publ_name[i]);
            }
        }

    }

    return 0;
}
