Object subclass: StatisticCounter [
    | fileContent lineCount charCount wordCount words wordFreq letterFreq |

    readfile: fileName [
        "read in file and initialize the stats"
        | f |
        lineCount := 0.
        "from franco's example"
        f := FileStream open: fileName mode: FileStream read.
        fileContent := WriteStream on: String new.
        f linesDo: [:line |
            lineCount := lineCount + 1.
            fileContent nextPutAll: line; nextPut: Character space.
        ].
        f close.
        self countChars.
        self countWords.
    ]

    countWords [
        "counts the words and stores in dict by iterating through words collection"
        | count |
        words := fileContent contents tokenize: '[^A-Za-z]+'.
        wordCount := words size.

        wordFreq := Dictionary new.
        words do: [:word |
            count := wordFreq at: word ifAbsent: [0].
            wordFreq at: word put: count + 1.
        ].
    ]

    countChars [
        "counts chars into dict, note lower and upper count for same char"
        | count lowerChar |
        charCount := 0.
        letterFreq := Dictionary new.
        fileContent contents do: [:char |
            (char isLetter) ifTrue: [
                charCount := charCount + 1.
                lowerChar := char asLowercase.
                count := letterFreq at: lowerChar ifAbsent: [0].
                letterFreq at: lowerChar put: count + 1.
            ].
        ].
    ]

    "getters"
    
    getWordFreq [ 
        ^wordFreq. 
    ]

    getLetterFreq [ 
        ^letterFreq. 
        ]
    getWordCount [ 
        ^wordCount. 
    ]

    getWords [ 
        ^words. 
    ]
    getCharCount [ 
        ^charCount. 
        ]
    getContent [ 
        ^fileContent contents. 
        ]
    getLineCount [ 
        ^lineCount. 
    ]

    printBox: text [
        "print box header with word given as an arg"
        | dashes |
        dashes := String new: (text size + 2) withAll: $-.
        '/' display. dashes display. '\' displayNl.
        '| ' display. text display. ' |' displayNl.
        '\' display. dashes display. '/' displayNl.
        Transcript nl.
    ]

    printSummary [
        "iterate through all keys in wordFreq (which is all the words)"
        | first |
        'Words in dictionary - ' display.
        first := true.
        wordFreq keys do: [:word |
            first ifFalse: [
                ', ' display
            ].
            word display.
            first := false.
        ].
        Transcript nl.
        Transcript nl.

        'Number of Letters : ' display. charCount displayNl.
        'Number of Words : ' display. wordCount displayNl.
        'Number of Lines : ' display. lineCount displayNl.
        Transcript nl.
    ]

    printLetterFreq [
        "displays the count of the chars based from the letterFreq dict"
        self printBox: 'Letter Freq'.
        'abcdefghijklmnopqrstuvwxyz' do: [:letter |
            | freq |
            freq := letterFreq at: letter ifAbsent: [0].
            letter display. 
            ' |' display.
            freq > 10
                ifTrue: [
                    (String new: 10 withAll: $*) display.
                    ' (' display. freq display. ')' displayNl.
                ]
                ifFalse: [
                    (String new: freq withAll: $*) displayNl.
                ].
        ].
        Transcript nl.
    ]

    printDictionary [
        "print dictionary from wordFreq keys and vals"
        | maxLen padding |
        self printBox: 'Dictionary'.
        'Word          Frequency' displayNl.
        '-------------------------' displayNl.

        maxLen := 0.
        wordFreq keys do: [:word |
            (word size > maxLen) ifTrue: [
                maxLen := word size
            ].
        ].

        wordFreq keysAndValuesDo: [:word :freq |
            word display.
            padding := String new: (maxLen - word size + 1) withAll: Character space.
            padding display.
            freq displayNl.
        ].
        Transcript nl.
    ]

    printHistogram [
        "prints amount of words in wordFreq in FANCY way"
        | wordList maxFreq numWords dashLen wordIndex maxLen |
        self printBox: 'Histogram'.

        wordList := wordFreq keys asArray.
        numWords := wordList size.

        "gets max length for starting spot"
        maxLen := 0.
        wordFreq keys do: [:word |
            (word size > maxLen) ifTrue: [
                maxLen := word size
            ].
        ].

        "gets max freq for height start"
        maxFreq := 0.
        wordFreq values do: [:f | (f > maxFreq) ifTrue: [
            maxFreq := f
        ]].

        "print * or spaces for freq of word"
        maxFreq to: 1 by: -1 do: [:row |
            (String new: maxLen withAll: Character space) display.
            wordList do: [:word |
                | freq |
                freq := wordFreq at: word.
                (freq >= row) ifTrue: [
                    '* ' display
                ] ifFalse: [
                    '  ' display
                ].
            ].
            Transcript nl.
        ].

        dashLen := maxLen + (numWords * 2).
        (String new: dashLen withAll: $-) displayNl.

        (String new: maxLen withAll: Character space) display.
        numWords timesRepeat: ['^ ' display].
        Transcript nl.

        "prints dashes for words ----------/"
        wordIndex := 0.
        wordList do: [:word |
            | dashCount remaining |
            word display.
            (String new: (maxLen - word size) withAll: Character space) display.
            dashCount := wordIndex * 2.
            (String new: dashCount withAll: $-) display.
            '/' display.
            remaining := numWords - wordIndex - 1.
            remaining timesRepeat: [' |' display].
            Transcript nl.
            wordIndex := wordIndex + 1.
        ].
    ]
]

" main----------------------------"

stats := StatisticCounter new.

'Please enter filename: ' display.
input := stdin nextLine.
stats readfile: input.
'--------------------------------------------------' displayNl.
Transcript nl.

stats printSummary.
stats printLetterFreq.
stats printDictionary.
stats printHistogram.
