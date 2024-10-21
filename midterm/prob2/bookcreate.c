#include <stdio.h>

int add_book(char(*book_name)[30], char(*author_name)[30], char(*publisher_name)[30],
	int* borrowed_book, int* total_book);
int search_book(char(*book_name)[30], char(*author_name)[30], char(*publisher_name)[30], 
	int total_book);

int compare(char* str1, char* str2);

int borrow_book(int* borrowed_book);
int return_book(int* borrowed_book);

int main(void) {

	int user_choice;
	int total_book = 0; 
	char book_name[100][30], author_name[100][30], publisher_name[100][30]; 
	int borrowed_book[100];

	while (1) {

		
		printf("1. 책 추가하기 \n");
		printf("2. 종료하기 \n");
		
		scanf("%d", &user_choice);
		printf("\n");

		switch (user_choice) {
		case 1:
			add_book(book_name, author_name, publisher_name, borrowed_book, &total_book);
			break;
		case 2:
			return 0;
		}

	}
}

int add_book(char(*book_name)[30], char(*author_name)[30], char(*publisher_name)[30],
	int* borrowed_book, int* total_book) {

    printf("id ");
	scanf("%s", book_name[*total_book]);
	
	printf("bookname ");
	scanf("%s", book_name[*total_book]);

	printf("author ");
	scanf("%s", author_name[*total_book]);

	printf("year ");
	scanf("%s", publisher_name[*total_book]);
	
	printf("numofborrow ");
	scanf("%s", publisher_name[*total_book]);
	
	printf("books ");
	scanf("%s", publisher_name[*total_book]);

	borrowed_book[*total_book] = 0;
	(* total_book)++;

	printf("\n");

	return 0;
}



