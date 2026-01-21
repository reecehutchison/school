"
-----------
Game Class: class name
-----------
lastRollValue : Integer 
runningScore : Integer
-----------
rollDice : changes value of lastRollValue attribute
getRollValue : returns lastRollValue
getRunningScore : returns runningScore
-----------
"
Object subclass: Game [
    | lastRollValue runningScore | 

    initialize [
        lastRollValue := 0.
        runningScore := 0.
    ]

    rollDice [
        lastRollValue := (Random new next * 6) truncated + 1.
        (lastRollValue ~= 1) ifTrue: [
            runningScore := runningScore + lastRollValue.
        ].
        ^lastRollValue
    ]

    setLastRollValue [
        lastRollValue := 1
    ]

    getLastRollValue [
        ^lastRollValue
    ]

    getRunningScore [
        ^runningScore
    ]
]

g := Game new.
g initialize.

[ g getLastRollValue ~= 1 ] whileTrue: [
    'Press <Enter> to roll or enter "q" to quit' print.
    input := stdin nextLine.
    (input ~= 'q') ifTrue: [
    ('You rolled a ', 
        g rollDice printString, 
        ' and your total is ', 
        g getRunningScore printString) 
    printNl.
    ].
    (input ~= 'q') ifFalse: [
        g setLastRollValue 
    ]
]

('You rolled a total of ', g getRunningScore printString) printNl