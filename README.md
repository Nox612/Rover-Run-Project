# Rover-Run-Project

complexity of creating tree: O(k+k*(k-1)+k*(k-2)+k*(k-3)+...+k*(k-n)) =  O((k!)/((k-n)!))
k: number of possible choices
n: number of moves chosen

complexity of searching through tree: O(k+k*(k-1)+k*(k-2)+k*(k-3)+...+k*(k-n)) =  O((k!)/((k-n)!))
k: number of possible choices
n: number of moves chosen

complexity of accessing the chosen leaf: O(n)
n: number of moves
