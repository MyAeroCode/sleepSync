### Cross-Platform sleepSync

|              | uwait | wait | waitKey | waitLine | waitEnter | waitConfirm |
| ------------ | ----- | ---- | ------- | -------- | --------- | ----------- |
| Unix / Linux | v     | v    | v       | v        | v         | v           |
| Windows      | v     | v    | v       | v        | v         | v           |
| Mac          |       |      |         |          |           |             |

#### Feature

-   [x] μs base wait
-   [x] ms base wait
-   [x] unicode support
-   [x] timeout

---

### Installation

require :

-   cmake
-   c/c++ compiler

```shell
npm install waait-sync
```

---

### Examples

#### uwait

```ts
import { uwait } from "waait-sync";
// or
const uwait = require("waait-sync").uwait;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Wait 333 μs.
    uwait(333);
}
```

#### wait

```ts
import { wait } from "waait-sync";
// or
const wait = require("waait-sync").wait;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Wait 333 ms.
    wait(333);
}
```

#### waitKey

```ts
import { waitKey } from "waait-sync";
// or
const waitKey = require("waait-sync").waitKey;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Wait for a key with the given ascii number to be pressed.
    // The code below waits for the ESC(ascii 27) key.
    waitKey(27);

    //
    // Wait only 333ms.
    // Returns false if timeout.
    waitKey(27, 333);
}
```

#### waitLine

```ts
import { waitLine } from "waait-sync";
// or
const waitLine = require("waait-sync").waitLine;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Wait for "Hello, World!" To be entered.
    waitLine("Hello, World!");

    //
    // Wait only 333ms.
    // Returns false if timeout.
    waitLine("Hello, World!", 333);

    //
    // unicode support.
    waitLine("안녕하세요!");
}
```

#### waitEnter

```ts
import { waitEnter } from "waait-sync";
// or
const waitEnter = require("waait-sync").waitEnter;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Wait for the Enter key to be pressed.
    waitEnter();

    //
    // Wait only 333ms.
    // Returns false if timeout.
    waitEnter(333);
}
```

#### waitConfirm

```ts
import { waitConfirm } from "waait-sync";
// or
const waitConfirm = require("waait-sync").waitConfirm;

for (let i = 0; i < 10; i++) {
    console.log(i);

    //
    // Returns true if "y" is entered.
    // Returns false if anything else is entered.
    if (waitConfirm("y")) break;

    //
    // Returns true if "y" is entered.
    // Returns false if "n" is entered.
    // Retry if anything esle is entered.
    if (waitConfirm("y", "n")) break;

    //
    // Wait only 333ms.
    if (waitConfirm("y", undefined, 333)) break;

    //
    // Unicode support.
    if (waitConfirm("네", "아니요")) break;
}
```