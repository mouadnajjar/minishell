

diagram of the t_cmd linked list:

head -> [t_cmd]
        ├── argv: ["echo", "hi", NULL]
        ├── redirs: [t_redirect{target: "file", type: 1}, t_redirect{target: NULL}]
        ├── is_pipe: 1
        ├── next: [t_cmd]
                   ├── argv: ["wc", NULL]
                   ├── redirs: [t_redirect{target: NULL}]
                   ├── is_pipe: 0

                   ├── next: cmd_2
//cmd_2 :

head -> [t_cmd]
        ├── argv: ["grep", "i", NULL]
        ├── redirs: [t_redirect{target: "file", type: 1}, t_redirect{target: NULL}]
        ├── is_pipe: 0
        ├── next: [t_cmd]
                   ├── argv: ["wc", NULL]
                   ├── redirs: [t_redirect{target: NULL}]
                   ├── is_pipe: 0
                   ├── next: NULL
