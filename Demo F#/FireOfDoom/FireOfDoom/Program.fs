open System
open System.Drawing
open System.Windows.Forms

let CJS_TICKER_FPS = 0
let FIRE_WIDTH = 256
let FIRE_HEIGHT = 256

let firePal = Array.zeroCreate 37
let firePixels = Array.zeroCreate (FIRE_WIDTH * FIRE_HEIGHT)
let fireRGB = [| 
    0x07; 0x07; 0x07; 0x1F; 0x07; 0x07; 0x2F; 0x0F; 0x07; 0x47; 0x0F; 0x07; 0x57; 0x17; 0x07; 0x67;
    0x1F; 0x07; 0x77; 0x1F; 0x07; 0x8F; 0x27; 0x07; 0x9F; 0x2F; 0x07; 0xAF; 0x3F; 0x07; 0xBF; 0x47;
    0x07; 0xC7; 0x47; 0x07; 0xDF; 0x4F; 0x07; 0xDF; 0x57; 0x07; 0xDF; 0x57; 0x07; 0xD7; 0x5F; 0x07;
    0xD7; 0x5F; 0x07; 0xD7; 0x67; 0x0F; 0xCF; 0x6F; 0x0F; 0xCF; 0x77; 0x0F; 0xCF; 0x7F; 0x0F; 0xCF;
    0x87; 0x17; 0xC7; 0x87; 0x17; 0xC7; 0x8F; 0x17; 0xC7; 0x97; 0x1F; 0xBF; 0x9F; 0x1F; 0xBF; 0x9F;
    0x1F; 0xBF; 0xA7; 0x27; 0xBF; 0xA7; 0x27; 0xBF; 0xAF; 0x2F; 0xB7; 0xAF; 0x2F; 0xB7; 0xB7; 0x2F;
    0xB7; 0xB7; 0x37; 0xCF; 0xCF; 0x6F; 0xDF; 0xDF; 0x9F; 0xEF; 0xEF; 0xC7; 0xFF; 0xFF; 0xFF |]

let buffer = new Bitmap(FIRE_WIDTH, FIRE_HEIGHT)

let setup () =
    let mutable i = 0
    let mutable palIndex = 0

    while palIndex < 37 do
        firePal.[palIndex] <- Color.FromArgb(fireRGB.[i], fireRGB.[i+1], fireRGB.[i+2])
        i <- i + 3
        palIndex <- palIndex + 1

    for i = 0 to (FIRE_WIDTH * FIRE_HEIGHT) - 1 do
        firePixels.[i] <- 0

    for i = 0 to FIRE_WIDTH - 1 do
        firePixels.[(FIRE_HEIGHT - 1) * FIRE_WIDTH + i] <- 36

let draw () =
    let graphics = Graphics.FromImage(buffer)
    graphics.Clear(Color.Black)
    doFire()

    for h = 0 to FIRE_HEIGHT - 1 do
        for w = 0 to FIRE_WIDTH - 1 do
            let p = firePixels.[h * FIRE_WIDTH + w]
            let color = firePal.[p]
            buffer.SetPixel(w, h, color)

    let fps = CJS_TICKER_FPS
    let text = sprintf "FPS: %.2f" fps
    let font = new Font("Arial", 12.0f)
    let brush = new SolidBrush(Color.White)
    graphics.DrawString(text, font, brush, PointF(10.0f, float(FIRE_HEIGHT - 20)))
    buffer.Save("fire.png", Imaging.ImageFormat.Png)

let spreadFire pixel curSrc counter srcOffset rand width =
    let mutable rand = rand
    if pixel <> 0 then
        let randIdx = (int (Math.Round (float (new Random().Next(256))))) &&& 255
        rand <- ((rand + 2) &&& 255)
        let tmpSrc = curSrc + (((counter - (randIdx &&& 3)) + 1) &&& (width - 1))
        firePixels.[tmpSrc - width] <- pixel - ((randIdx &&& 1))
    else
        firePixels.[srcOffset - width] <- 0
    rand

let doFire () =
    let mutable counter = 0
    let mutable curSrc = 0
    let mutable srcOffset = 0
    let mutable rand = 0
    let mutable step = 0
    let mutable pixel = 0
    let mutable i = 0

    rand <- (new Random()).Next(256)
    curSrc <- FIRE_WIDTH

    while counter < FIRE_WIDTH do
        srcOffset <- curSrc + counter
        pixel <- firePixels.[srcOffset]
        step <- 2

        rand <- spreadFire pixel curSrc counter srcOffset rand FIRE_WIDTH

        curSrc <- curSrc + FIRE_WIDTH
        srcOffset <- srcOffset + FIRE_WIDTH

        let mutable innerStep = 0
        innerStep <- 0
        while innerStep < FIRE_HEIGHT do
            pixel <- firePixels.[srcOffset]
            step <- step + 2

            rand <- spreadFire pixel curSrc counter srcOffset rand FIRE_WIDTH

            pixel <- firePixels.[srcOffset + FIRE_WIDTH]
            curSrc <- curSrc + FIRE_WIDTH
            srcOffset <- srcOffset + FIRE_WIDTH

            rand <- spreadFire pixel curSrc counter srcOffset rand FIRE_WIDTH

            curSrc <- curSrc + FIRE_WIDTH
            srcOffset <- srcOffset + FIRE_WIDTH
            innerStep <- innerStep + 2

        counter <- counter + 1
        curSrc <- curSrc - ((FIRE_WIDTH * FIRE_HEIGHT) - FIRE_WIDTH)

[<EntryPoint>]
let main argv =
    setup()
    draw()
    0 // return an integer exit code
