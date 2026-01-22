Object subclass: Game [
    | playerCredits winningRolls losingRolls| 

    initialize [
        playerCredits := 100.

        winningRolls := Set new.
        winningRolls add: #(4 5 6).    
        winningRolls add: #(1 1 1).   
        winningRolls add: #(2 2 2).
        winningRolls add: #(3 3 3).
        winningRolls add: #(4 4 4).
        winningRolls add: #(5 5 5).
        winningRolls add: #(6 6 6).
        winningRolls add: #(1 1 6).    
        winningRolls add: #(2 2 6).
        winningRolls add: #(3 3 6).
        winningRolls add: #(4 4 6).
        winningRolls add: #(5 5 6).

        losingRolls := Set new.
        losingRolls add: #(1 2 3).     
        losingRolls add: #(1 2 2).     
        losingRolls add: #(1 3 3).
        losingRolls add: #(1 4 4).
        losingRolls add: #(1 5 5).
        losingRolls add: #(1 6 6).
    ]

    rollDice [
        | roll |

        roll := Array new: 3.
        roll at: 1 put: (Random new next * 6) truncated + 1.
        roll at: 2 put: (Random new next * 6) truncated + 1.
        roll at: 3 put: (Random new next * 6) truncated + 1.

        ^roll := roll asSortedCollection asArray.
        
    ]

    getPoint: roll [
        ((roll at: 1) = (roll at: 2)) ifTrue: [^(roll at: 3)].
        ((roll at: 2) = (roll at: 3)) ifTrue: [^(roll at: 1)].
        ^nil.
    ]

    turn [
        | roll point |

        roll := self rollDice.
        (winningRolls includes: roll) ifTrue: [^6].
        (losingRolls includes: roll) ifTrue: [^1].

        point := self getPoint: roll.
        (point notNil) ifTrue: [^point].

        ^self turn.
    ]

    addCredit: val [
        playerCredits := playerCredits + val.
    ]

    subCredit: val [
        playerCredits := playerCredits - val.
    ]

    getCredit [
        ^playerCredits.
    ]
]

"-------- application logic --------"
| bankRoll playerRoll playerBet input |

g := Game new.
g initialize.
input := ''.

'Welcome to the Ceelo game' printNl.

[((g getCredit) > 0) & (input ~= 'q')] whileTrue: [
    'You have ' print. (g getCredit) print. ' credits.' printNl.
    'Press <Enter> to roll or enter "q" to quit: ' print.
    input := stdin nextLine.

    (input ~= 'q') ifTrue: [
        'Please make your bet (1-' print. (g getCredit) print. '): ' print.
        playerBet := (stdin nextLine) asInteger.

        [(playerBet < 1) | (playerBet > (g getCredit))] whileTrue: [
            'Invalid bet. Please bet between 1 and ' print. (g getCredit) print. ': ' print.
            playerBet := (stdin nextLine) asInteger.
        ].

        bankRoll := g turn.
        'Bank rolled: ' print. bankRoll printNl.

        (bankRoll = 6) ifTrue: [
            'Bank hit a 6, you lose!' printNl.
            g subCredit: playerBet.
        ].

        (bankRoll = 1) ifTrue: [
            'Bank hit a 1, you win!' printNl.
            g addCredit: playerBet.
        ].

        ((bankRoll >= 2) & (bankRoll <= 5)) ifTrue: [
            'Bank established point: ' print. bankRoll printNl.
            playerRoll := g turn.
            'You rolled: ' print. playerRoll printNl.

            (playerRoll > bankRoll) ifTrue: [
                'You win!' printNl.
                g addCredit: playerBet.
            ].
            (playerRoll < bankRoll) ifTrue: [
                'You lose!' printNl.
                g subCredit: playerBet.
            ].
            (playerRoll = bankRoll) ifTrue: [
                'Tie! Bet returned.' printNl.
            ].
        ].
    ].
].

'Thanks for playing! Final credits: ' print. (g getCredit) printNl.
