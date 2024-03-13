open System

let width = 50
let height = 50

let initGrid () =
    Array2D.init width height (fun _ _ -> if Random().Next(2) = 0 then 0 else 1)

let printGrid (grid: int[,]) =
    for y in 0 .. height - 1 do
        for x in 0 .. width - 1 do
            printf "%c " (if grid.[x, y] = 0 then '.' else '#')
        printfn ""

let getNeighbors (x, y) =
    [ (x-1, y-1); (x, y-1); (x+1, y-1);
      (x-1, y);             (x+1, y);
      (x-1, y+1); (x, y+1); (x+1, y+1) ]

let getAliveNeighborsCount (grid: int[,]) (x, y) =
    getNeighbors (x, y)
    |> List.filter (fun (nx, ny) -> nx >= 0 && nx < width && ny >= 0 && ny < height && grid.[nx, ny] = 1)
    |> List.length

let updateCell (grid: int[,]) (x, y) =
    let aliveNeighbors = getAliveNeighborsCount grid (x, y)
    if grid.[x, y] = 1 then
        if aliveNeighbors < 2 || aliveNeighbors > 3 then 0 else 1
    else
        if aliveNeighbors = 3 then 1 else 0

let updateGrid (grid: int[,]) =
    Array2D.init width height (fun x y -> updateCell grid (x, y))

let rec runSimulation (grid: int[,]) =
    Console.Clear()
    printGrid grid
    System.Threading.Thread.Sleep(500)
    let newGrid = updateGrid grid
    runSimulation newGrid

[<EntryPoint>]
let main argv =
    let initialGrid = initGrid ()
    runSimulation initialGrid
    0 // return an integer exit code
