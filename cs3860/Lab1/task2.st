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
        runningScore := runningScore + lastRollValue.
        ^lastRollValue
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
   'Press <Enter> to roll' print.
    stdin nextLine.
   ('You rolled a ', g rollDice printString, ' and your total is ', g getRunningScore printString) printNl.
]

('You got ', g getRunningScore printString) printNl