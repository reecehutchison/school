r := Random new.
roll := 0.
count := 0.

rollDice := [roll := r between: 1 and:6].
addCount := [:val | count := count + val].
subCount := [:val | count := count - val].

[(roll ~= 1)] whileTrue: [
    
    Transcript show: 'Please <Enter> to roll'.
    stdin nextLine.
    
    rollDice value.
    addCount value: roll.

    Transcript show: 'You rolled a ', (roll asString); cr.
].

subCount value: 1.
Transcript show: ('You rolled a total of ', count asString), ' before rolling a 1.'; cr.





