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
(g rollDice) printNl.
(g rollDice) printNl.
(g getRunningScore) printNl