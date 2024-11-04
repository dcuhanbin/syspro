#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s [옵션]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'e': {
                    if (strlen(argv[i]) > 2) {
                        // 환경 변수 이름이 주어진 경우
                        char *env_name = argv[i] + 2;
                        char *env_value = getenv(env_name);
                        if (env_value != NULL) {
                            printf("환경 변수 %s: %s\n", env_name, env_value);
                        } else {
                            printf("환경 변수 %s가 설정되지 않았습니다.\n", env_name);
                        }
                    } else {
                        // 환경 변수 이름이 주어지지 않은 경우, 모든 환경 변수 출력
                        extern char **environ;
                        for (char **env = environ; *env != NULL; env++) {
                            printf("%s\n", *env);
                        }
                    }
                    break;
                }
                case 'u': {
                    printf("실제 사용자 ID: %d\n", getuid());
                    printf("유효 사용자 ID: %d\n", geteuid());
                    break;
                }
                case 'g': {
                    printf("실제 그룹 ID: %d\n", getgid());
                    printf("유효 그룹 ID: %d\n", getegid());
                    break;
                }
                case 'i': {
                    printf("프로세스 ID: %d\n", getpid());
                    break;
                }
                case 'p': {
                    printf("부모 프로세스 ID: %d\n", getppid());
                    break;
                }
                default:
                    fprintf(stderr, "알 수 없는 옵션: %s\n", argv[i]);
            }
        }
    }

    return 0;
}

