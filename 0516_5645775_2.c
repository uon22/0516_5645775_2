#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    printf("삽입시 링크를 따라 이동한 횟수 : 1\n");
    return p;
}

ListNode* insert(ListNode* head, ListNode* pre, element value, int count) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    printf("삽입시 링크를 따라 이동한 횟수 : %d\n", count);
    return head;
}

ListNode* delete_first(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode* removed = head;
    head = head->link;
    free(removed);
    printf("삭제시 링크를 따라 이동한 횟수 : 1\n");
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre, int count) {
    ListNode* removed = pre->link;
    pre->link = removed->link;
    free(removed);
    printf("삭제시 링크를 따라 이동한 횟수 : %d\n", count);
    return head;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%d -> ", p->data);
    }
    printf("NULL\n");
}

int get_length(ListNode* head) {
    int length = 0;
    for (ListNode* p = head; p != NULL; p = p->link) {
        length++;
    }
    return length;
}

int main() {
    ListNode* head = NULL;
    int choice, position, value;

    while (1) {
        printf("메뉴 : \n");
        printf("1. 리스트에 추가\n");
        printf("2. 리스트에서 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("선택하세요 : ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 숫자를 입력하세요 : ");
            scanf_s("%d", &value);
            printf("추가할 위치를 입력하세요 : ");
            scanf_s("%d", &position);

            if (position < 0) {
                printf("유효하지 않은 위치입니다.\n");
                break;
            }

            if (position == 0) {
                head = insert_first(head, value);
            }
            else {
                int length = get_length(head);
                if (position > length) {
                    position = length;
                }
                ListNode* pre = head;
                int count = 1;
                while (count < position && pre != NULL) {
                    pre = pre->link;
                    count++;
                }
                if (pre == NULL) {
                    printf("유효하지 않은 위치입니다.\n");
                }
                else {
                    head = insert(head, pre, value, count + 1);
                }
            }
            break;

        case 2:
            printf("삭제할 위치를 입력하세요 : ");
            scanf_s("%d", &position);

            if (position < 0) {
                printf("유효하지 않은 위치입니다.\n");
                break;
            }

            if (position == 0) {
                head = delete_first(head);
            }
            else {
                ListNode* pre = head;
                int count = 1;
                while (count < position && pre != NULL) {
                    pre = pre->link;
                    count++;
                }
                if (pre == NULL || pre->link == NULL) {
                    printf("유효하지 않은 위치입니다.\n");
                }
                else {
                    head = delete(head, pre, count + 1);
                }
            }
            break;

        case 3:
            print_list(head);
            break;

        case 0:
            exit(0);

        default:
            printf("유효하지 않은 선택입니다!\n");
        }
    }

    return 0;
}