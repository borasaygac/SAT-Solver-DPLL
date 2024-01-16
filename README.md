# Group_K_Project_2
Files in which we timeout for all heuristics:
- 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 
- 35, 36, 37, 38, 39, 40, 42, 43, 44, 77
- 78, 79, 

Intersting results: 
- Normal order => DLCS < DLIS < JW < INC => So INC is normally the slowest
- Usually JW solves some seconds after DLIS, DLCS by far the fastest, and INC the slowest
- 41 aim 200 SAT-> only with INC 
- For big aim problems, if INC can solve it than JW is slower than INC
- 48 aim 200 sat -> INC 29, DLIS 16, DLCS 22, JW 25 -> Instance where DLIS is fastest
- 56 aim 50 SAT -> DLCS solves with 22 choose and 21 backtrack, inc with 9k choose, and 9k backtrack (64 aim is similar)
- 61 aim 50 SAT -> JW solves with 43 choose and 37 backtrack, dlcs 2k each, dlis 3k each, inc 500 each
- 62 aim 50 SAT -> INC solves with 157 choose, 150 backtrack, dlis 280 each, dlcs 750 each, JW 370 each
- 66 aim 50 SAT -> inc solves with 2 choices no backtrack, DLIS 130 each, DLCS 130 each, JW 130 each.
- 68 aim 50 SAT -> DLIS and JW with 9 choose and 2 backtrack, Inc with 190 each, dlcs 40 each
- 70 aim 50 SAT -> DLIS with 7 choose no backtrack, DLCS 7 choose 1 backtrack, time diff = 1.016492 , 1.001649 => DLCS faster regardless 
- 81 ii16c1 SAT -> only dlcs solves and that with a whooping 1.044 secs
- 84 ii16d2 SAT -> DLIS and JW with 40 choose 4 backtrack
- 87 ii32a1 SAT -> DLIS and JW with 5 choose 3 backtrack
- For big ii16 and 32s jw and DLIS seem to perform similarly
- 101 ii31e3 SAT -> DLIS with just 3 choose no backtrack, JW the same
- 106 ii8a3 SAT -> INC leaves the others in its dust -> 1 Sec < 106 < 93 < 115
- 111 ii8b4 SAT -> DLCS TIMES OUT (woah!) Inc with a sec, the king (DLCS) is dead, long live the king (INC) -- DLCS resurrects a couple cases later






Cactus Plot Sat Solver -- https://github.com/alexeyignatiev/mkplot

C15 takes 57 second with DLCS -- on the border

TODO: OPTIMIERUNG (COPY necc, if necc, etc....), PURELIT, HEURISTICS APPROACH, FORCED QUEUE, REMOVE DUPLICATES PER CLAUSE


Global vars: # vars (n), # clauses (m), _Variable_ and _Clause_ data structure, unit_queue Queue<int>, assig_stack Stack<int>.

**_Clause_**: Representation of a clause
- SAT_by (int) 
- list of literals ([int])
- number of active literals (int), initially: len(literals)

**_Variable_**: Representation of a variable
- val (true, false, free)
- pos_occ: the list of clauses the variable occurs positively in ([int])
- neg_occ: -||- ([int])
- forced: Was the assigned val a reslut of branching (forced == false) or UP (forced == true)

(Personal) Suggestion: Keep two arrays, one of type _Clause_, one of type _Variable_. For both arrays, the index represent the respective clause / variable, i.e. given the first clause of the DIMACS file, its clause has index 0. Variables are already represented as integers by DIMACS. Size of arrays will be set through header of DIMACS file / Global variables m, n.

After init of both arrays, start DPLL:

Choose variable i to be set to true or false.

**1. Unit Propagation**

    - iterate over both pos_occ and neg_occ and for the former: SAT_by := i, the latter: decrement active.
    - if active == 1 => add those to unit queue for later treatment
    - if active == 0 => conflict => backtrack!

**2. Backtracking**
    
    We want to backtrack up until our last branching variable

    while assig_stack.peek().forced: // assig is result of UP
        var = assig_stack.pop()
        var.val = free

        for every clause C in var.pos_occ:
            if clause.SAT_by == var:
                reset clause.SAT_by

        for every clause C in var.neg_occ:
            increment active
    
    if assig_stack.isEmpty():
        return UNSAT; // we backtracked to the beginning of our assignment procedure

    unit_queue.clear() // gained unit clauses bear no value

    b = assig_stack.peek() // branching variable

    b.val = !b.val //start DPLL with negated assignment of var

    resume with UP

## Getting started
Makefile extension VS Code
GCC compiler
Run ```
make run arg=...```

on root directory.

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab2.cip.ifi.lmu.de/abawi/group_k_project_2.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://gitlab2.cip.ifi.lmu.de/abawi/group_k_project_2/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Set auto-merge](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing(SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thank you to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
