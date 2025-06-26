#include "../../minishell.h"

// void heredoc(t_heredoc *com)
// {
//     int fd;
//     // t_heredoc *redi;
//     int id;
//     char *gel;
//     // com->head

//     fd = open(".file_tmp", O_CREAT | O_TRUNC | O_RDONLY | O_RDWR, 0777);// fix 0777
//     if(fd < 0)
//         return ;
//     // com->type = RED_IN;
//     id = fork();
//     if (id == 0)
//     {
//         // printf("%s\n", redi->delimiter);
//         // redi->delimiter = ft_strjoin(redi->delimiter, "\n");
//         while (1)
//         {
//             // write(1, ">", 1);
//             gel = readline("> ");
//             // dprintf(2, "%s", gel);
//             if(!gel || ft_strcmp(com->delimiter, gel) == 0)
//                 break;
//             write(fd, gel, ft_strlen(gel));
//         }
//         close(fd);
//         exit(0);
//     }
//     wait(NULL);
//     com->delimiter = ".file_tmp";
//     close(fd);
// }

void heredoc(t_min *min)
{
    int fd;
    int id;
    char *gel;

    fd = open(".file_tmp", O_CREAT | O_TRUNC | O_RDONLY | O_RDWR, 0777);// fix 0777
    if(fd < 0)
        return ;
    id = fork();
    if (id == 0)
    {
        min->head->delimiter = ft_strjoin(min->head->delimiter, "\n");
        while (1)
        {
            write(1, ">", 1);
            gel = get_next_line(0);
            if(!gel || ft_strcmp(min->head->delimiter, gel) == 0)
                break ;
            write(fd, gel, ft_strlen(gel));
        }
        close(fd);
        exit(0);
    }
    wait(NULL);
    min->head->file_name = ".file_tmp";
    close(fd);
}
