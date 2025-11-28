import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final String fileName = "./cs3790/assignment5/data.text";
        FileService fs = new FileService(fileName);
        List<String> arr = fs.getData();
        SimSystem ss = new SimSystem(arr);
        Scanner scanner = new Scanner(System.in);

        System.out.println("--- Bankers Algorithm Sim ---\n"); // POV: THE BANKER IS READY TO DO HIS THING.
        ss.sysPrint();                                         //          .-'-.
        System.out.println();                                  //       /`     |__
                                                               //     /`  _.--`-,-`
        int inputProcess = 99999;                              //     '-|`   a '<-.   []
                                                               //       \     _\__) \=`
        // main lop                                            //        C_  `    ,_/
        while (inputProcess >= 0) {                            //          | ;----'
            System.out.print("Enter a process (int): ");
            if (scanner.hasNextInt()) {
                inputProcess = scanner.nextInt();
            } else {
                scanner.next();
                System.out.println("Invalid, enter int only");
                continue;
            }

            if (inputProcess < 0) {
                break;
            }

            List<Integer> reqs = new ArrayList<Integer>();
            reqs.add(inputProcess);

            int[] requestArray = new int[ss.getResourceCount()];
            boolean validResources = true;

            for (int i = 0; i < ss.getResourceCount(); i++) {
                System.out.print("Enter a value for " + (char)('A' + i) + " (int): ");
                if (scanner.hasNextInt()) {
                    int resourceVal = scanner.nextInt();
                    reqs.add(resourceVal);
                    requestArray[i] = resourceVal;
                } else {
                    scanner.next();
                    System.out.println("Invalid, enter int only");
                    validResources = false;
                    break;               // THE BAT MAN MUST MAKE SURE YOU'RE REQUEST IS SAFE, BAT MAN HATES UNSAFETY
                }                        //     ,*-~"`^"*u_                                _u*"^`"~-*,
            }                            //  p!^       /  jPw                            w9j \        ^!p
                                         //w^.._      /      "\_                      _/"     \        _.^w
            if (!validResources) {       //     *_   /          \_      _    _      _/         \     _*
                System.out.println();    //       q /           / \q   ( `--` )   p/ \          \   p
                continue;                //       jj5****._    /    ^\_) o  o (_/^    \    _.****6jj
            }                            //                *_ /      "==) ;; (=="      \ _*
                                         //                 `/.w***,   /(    )\   ,***w.\"
            if (ss.BankersAlg(reqs)) {   //                  ^      ^c/ )    ( \c^      ^
                ss.commitRequest(inputProcess, requestArray);//      'V')_)(_('V'
            }                                                //          `` ``

            System.out.println();
            ss.sysPrint();
            System.out.println();
        }

/*                          THE ANTEATER SCOOPS UP ANY PESKY BUGS IN THE CODE
       _.---._    /\\       EVERYTHING IS CORRECT, HAS TO BE. MUST BE.
    ./'       "--`\//       HOPEFULLY.
  ./              o \          .-----.
 /./\  )______   \__ \        ( help! )
./  / /\ \   | \ \  \ \       /`-----'
   / /  \ \  | |\ \  \7--- ooo ooo ooo ooo ooo ooo
--------------------------------------------------
*/
        System.out.println("Thank you for using the Bankers Algorithm Sim, Goodbye");
        scanner.close(); // close scanner bro!
    }
}