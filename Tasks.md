## Tasks

| Task                | Status | Notes                     | Dependencies		|	Person in charge
|---------------------|--------|---------------------------|--------------------|---------------------
| Parse prompt        | [2]    | Implement parsing logic   |	Pipe			| Pilou & Giulio	|
| Import env          | [2]    | Load environment vars     |					| Pilou				|
| Pipe                | [0]    | Implement pipe handling   |					| Giulio			|
| $?                  | [0]    | Handle exit status        |					| Pilou				|
| Ctrl-C              | [1]    | Handle signal interruption|	exit			| Giulio			|
| Ctrl-D              | [1]    | Handle EOF signal         |	exit			| Giulio			|
| Ctrl-\              | [1]    | Handle quit signal        |	exit			| Giulio			|
| exec ./             | [2]    | Handle quit signal        |	exit			| Giulio			|
| Echo -n             | [2]    | Implement echo options    |					| Pilou				|
| cd                  | [2]    | Implement: ~, -, relative |					| Giulio			|
| pwd                 | [2]    | Print working directory   |					| Giulio			|
| export              | [2]    | Set environment variables |	env				| Pilou				|
| unset               | [2]    | Remove environment vars   |					| Pilou				|
| env                 | [2]    | Display environment vars  |	Import env		| Pilou				|
| exit                | [2]    | Exit shell properly       |					| Giulio			|
| "<>" redirection    | [0]    | Handle file redirection   | 					| Giulio			|

[0] Not started
[1] In progress
[2] Working
[3] Finished

## Notes

- [0] Cool start animation
- [0] Pipe
- [0] Error Check
- [0] Gestion ctrl_c et autre
- [0] Import Environment
- [0] Check tokenization
- [0] Implement objects file in makefile
