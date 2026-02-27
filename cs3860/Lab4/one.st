| inputString chunkSize i n curr k result |

'Enter a string: ' display.
inputString := stdin nextLine.
'Enter a chunk size: ' display.
chunkSize := (stdin nextLine) asInteger.

n := inputString size.
i := 0.
result := OrderedCollection new.

[i < n] whileTrue: [
  curr := ''.
  k := 0.

  [(i < n) and: [k < chunkSize]] whileTrue: [
    curr := curr, ((inputString at: (i + 1)) asString).
    k := k + 1.
    i := i + 1.
  ].

  result add: curr.
].

1 to: (result size) do: [:j |
  (result at: j) display.
  ' ' display.
].

'' displayNl. 