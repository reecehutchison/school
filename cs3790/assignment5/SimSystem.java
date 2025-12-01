import java.util.List;

public class SimSystem {
    private final int processCount;
    private final int resourceCount;
    private int[][] maxMatrix;
    private int[][] allocationMatrix;
    private int[][] needMatrix;
    private int[] resourceVector;

    public SimSystem(List<String> arr) {
        processCount = Integer.parseInt(arr.get(0));
        resourceCount = Integer.parseInt(arr.get(1));

        maxMatrix = new int[processCount][resourceCount];
        resourceVector = new int[resourceCount];

        allocationMatrix = new int[processCount][resourceCount];
        needMatrix = new int[processCount][resourceCount];

        int ptr = 2;
        // read max matrix from file data
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                maxMatrix[i][j] = Integer.parseInt(arr.get(ptr));
                ptr++;
            }
        }

        // read available vector
        for (int i = 0; i < resourceCount; i++) {
            resourceVector[i] = Integer.parseInt(arr.get(ptr));
            ptr++;
        }


        // calculate initial need
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
            }
        }
    }

    private void printSpaces(int n) {
        for (int i = 0; i < n; i++) System.out.print(" ");
    }
/*
                                         |
                                         |
                                         |
                                         |
   _______                   ________    |       "Surely this Robot can fend
  |ooooooo|      ____       | __  __ |   |       off any bugs right Tom?"
  |[]+++[]|     [____]      |/  \/  \|   |
  |+ ___ +|     ]()()[      |\__/\__/|   |       "Yeh but, we could have just
  |:|   |:|   ___\__/___    |[][][][]|   |       gave that ant eater a call
  |:|___|:|  |__|    |__|   |++++++++|   |       instead of spending years of
  |[]===[]|   |_|_/\_|_|    | ______ |   |       our lives and our entire lively
_ ||||||||| _ | | __ | | __ ||______|| __|       hoods on this..."
  |_______|   |_|[::]|_|    |________|   \
              \_|_||_|_/                  \
                |_||_|                     \
               _|_||_|_                     \
      ____    |___||___|                     \
     /  __\          ____                     \
     \( oo   blah   (___ \                     \
     _\_o/ blah      oo~)/
    / \|/ \         _\-_/_
   / / __\ \___    / \|/  \
   \ \|   |__/_)  / / .- \ \
    \/_)  |       \ \ .  /_/
     ||___|        \/___(_/
     | | |          | |  |
     | | |          | |  |
     |_|_|          |_|__|
     [__)_)        (_(___]
 */
    public void sysPrint() {
        int cell = 4;
        int dataWidth = resourceCount * cell;


        int colWidth = dataWidth + 4;

        System.out.print("Process   ");

        String[] headerStrings = {"Allocation", "Max", "Resources", "Need"};
        int[] headerLengths = {10, 3, 9, 4};

        // print main headers
        for (int k = 0; k < 4; k++) {
            String header = headerStrings[k];
            int headerLen = headerLengths[k];
            int effectiveWidth = Math.max(headerLen, dataWidth);
            int leftPad = (effectiveWidth - headerLen) / 2;

            printSpaces(leftPad);
            System.out.print(header);

            printSpaces(colWidth - leftPad - headerLen);
        }
        System.out.println();


        // print A B C... headers
        System.out.print("          ");
        for (int k = 0; k < 4; k++) {
            int headerLen = headerLengths[k];
            int effectiveWidth = Math.max(headerLen, dataWidth);
            int leftPad = (effectiveWidth - dataWidth) / 2;
            printSpaces(leftPad);
            for (int j = 0; j < resourceCount; j++) {
                System.out.printf("%" + cell + "s", (char)('A' + j));
            }

            printSpaces(colWidth - dataWidth - leftPad);
        }
        System.out.println();


        // print all the data rows
        for (int i = 0; i < processCount; i++) {
            System.out.printf("%-10s", "  P" + i);

            for (int k = 0; k < 4; k++) {
                int headerLen = headerLengths[k];
                int effectiveWidth = Math.max(headerLen, dataWidth);
                int leftPad = (effectiveWidth - dataWidth) / 2;



                printSpaces(leftPad);

                if (k == 0) {
                    for (int j = 0; j < resourceCount; j++) System.out.printf("%" + cell + "d", allocationMatrix[i][j]);
                } else if (k == 1) {
                    for (int j = 0; j < resourceCount; j++) System.out.printf("%" + cell + "d", maxMatrix[i][j]);
                } else if (k == 2) {
                    // available vector only printed once
                    if (i == 0) {
                        for (int j = 0; j < resourceCount; j++) System.out.printf("%" + cell + "d", resourceVector[j]);
                    } else {
                        printSpaces(dataWidth);
                    }

                } else {
                    for (int j = 0; j < resourceCount; j++) System.out.printf("%" + cell + "d", needMatrix[i][j]);
                }

                printSpaces(colWidth - dataWidth - leftPad);
            }
            System.out.println();
        }
    }

    public boolean BankersAlg(List<Integer> arr) {
        if (arr.size() != resourceCount + 1) return false;                // o
                                                                          //  \_/\o
        int pID = arr.get(0);                                             // ( Oo)                    \|/
        if (pID < 0 || pID >= processCount) return false;                 // (_=-)  .===O-  ~~Z~A~P~~ -O-
                                                                          //./   \_/U'                /|\
        int[] req = new int[resourceCount];                               // ||  |_/
        for (int i = 0; i < resourceCount; i++) {                         // \\  |
            req[i] = arr.get(i + 1);                                      // {K ||
        }                                                                 //  | PP
                                                                          // | ||
        for (int i = 0; i < resourceCount; i++) {                         // (__\\
            // check if request is more than need                         ----------------------------------------
            if (req[i] > needMatrix[pID][i]) {
                System.out.println("-> Request denied: P" + pID + " request exceeds its current need for resource " + (char)('A' + i));
                return false;
            }


            // check if request is more than available
            if (req[i] > resourceVector[i]) {
                System.out.println("-> Request denied: P" + pID + " must wait (not enough resources currently available).");
                return false;
            }
        }

        int[] availableTemp = resourceVector.clone();
        int[][] allocationTemp = new int[processCount][resourceCount];

        int[][] needTemp = new int[processCount][resourceCount];

        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                allocationTemp[i][j] = allocationMatrix[i][j];
                needTemp[i][j] = needMatrix[i][j];
            }
        }

        // simulate resource allocation
        for (int i = 0; i < resourceCount; i++) {
            availableTemp[i] -= req[i];
            allocationTemp[pID][i] += req[i];
            needTemp[pID][i] -= req[i];
        }
        if (isSafe(availableTemp, allocationTemp, needTemp)) {
            System.out.println("-> SUCCESS: Request granted. System stays in a safe state.");
            return true;
        } else {
            System.out.println("-> FAILURE: Request not granted. System becomes not in safe state.");
            return false;
        }
    }
/*
           |    |              _.-7
           |\.-.|             ( ,(_
           | a a|              \\  \,
           ) ["||          _.--' \  \\
        .-'  '-''-..____.-'    ___)  )\                           "THE CITY NEEDS ME,
       F   _/-``-.__;-.-.--`--' . .' \_L_                         I HAVE TO KEEP THINGS
      |   l  {~~} ,_\  '.'.      ` __.' )\                        SAFE."
      (    -.;___,;  | '- _       :__.'( /
      | -.__ _/_.'.-'      '-._ .'      \\
      |     .'   |  -- _                 '\,
      |  \ /--,--{ .    '---.__.       .'  .'
      J  ;/ __;__]. '.-.            .-' )_/
      J  (-.     '\'. '. '-._.-.-'--._ /
      |  |  '. .' | \'. '.    ._       \
      |   \   T   |  \  '. '._  '-._    '.
      F   J   |   |  '.    .  '._   '-,_.--`
      F   \   \   F .  \    '.   '.  /
     J     \  |  J   \  '.   '.    '/
     J      '.L__|    .   \    '    |
     |   .    \  |     \   '.   '. /
     |    '    '.|      |    ,-.  (
     F   | ' ___  ',._   .  /   '. \
     F   (.'`|| (-._\ '.  \-      '-\
     \ .-'  ( L `._ '\ '._ (
     /'  |  /  '-._\      ''\
         `-'
 */
    private boolean isSafe(int[] available, int[][] allocation, int[][] need) {
        int n = processCount;
        int m = resourceCount;

        int[] work = available.clone();
        boolean[] finish = new boolean[n];
        int count = 0;

        while (count < n) {
            boolean found = false;

            for (int i = 0; i < n; i++) {
                if (!finish[i]) {
                    boolean canFinish = true;
                    // check if the need <= work for current process
                    for (int j = 0; j < m; j++) {
                        if (need[i][j] > work[j]) {
                            canFinish = false;
                            break;
                        }
                    }

                    if (canFinish) {
                        // add allocation back to work if it is done
                        for (int j = 0; j < m; j++) {
                            work[j] += allocation[i][j];
                        }
                        finish[i] = true;
                        count++;
                        found = true;
                    }
                }
            }

            if (!found && count < n) {
                return false;
            }
        }
        return true;
    }

/************************************************************
                      \$
                       $)
                      ($`
                       $_
                    ,--" l_
                    ;|    )l
                    :    _/
                    ;   : l`.
           .-----._ L_..; :  \.-""""""-.
        _.'       -"   :   ; `-.        `.
      .'/              :   :   :   `.     \
     /    ,--,   ,     ; _, ;  :     \     \               Why did the programmer and his
    /    /   :   :  , :-"   :   \     \     ;              girlfriend break up?
   /   _:   /    ;-:  ;     :    \     ;   \:
  / .-/ ; ;:\   /: :  :     ;_.   \    :    \;             They had commit issues.
 /.'   : / :(.-" ; ;   ;   :/`.    \    ;    :
::     ;    \;  / /   /:   ; / \    `.  :     ;            -- Spiderman out
;:    : .-   ; : :.-./  \_/.'   \     `-:     :
: \   ;/     : ; ;  /`-   /      j       `.   ;
 ; `-.:      ; ; ;.'   \_g,     / ; ;      j :
 :     j    /  : :    ,-dP-'"--:  ; :     / ;;
  \__.' \_.'    \ \  _ s")    / \ :._;_.-'  ::
            bug  \   ;:      :   ; \ :      ::
                  \  ;;     /;   :  `.\      ;
                   ; ::\__.'/;__.:---.\     :
                   : ;  -.-'/___       \  _.;
                   : :`-. )",--"     ,--"" /
                   ; .;__T+'"""-._   :   .'
                  :,'     ;       ""-^-""
                  ;  _    :
                 :  / \   /;
                 ; :   \ / :
                 : ;_.-' `.;
                  \       /
                   `.___.'
*/
    public void commitRequest(int pID, int[] req) {
        for (int i = 0; i < resourceCount; i++) {
            resourceVector[i] -= req[i];
            allocationMatrix[pID][i] += req[i];

            needMatrix[pID][i] -= req[i];
        }


        boolean done = true;
        for (int i = 0; i < resourceCount; i++) {
            if (needMatrix[pID][i] != 0) {
                done = false;
                break;
            }
        }
        if (done) {
            System.out.println("-> P" + pID + " has finished!");

            // release resources and reset allocation
            for (int i = 0; i < resourceCount; i++) {
                resourceVector[i] += allocationMatrix[pID][i];

                allocationMatrix[pID][i] = 0;
            }

        }
    }

    public int getResourceCount() { return resourceCount; }
}