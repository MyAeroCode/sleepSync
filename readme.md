### Cross-Platform sleepSync

|              | uwait | wait | waitKey | waitLine | waitEnter | waitConfirm |
| ------------ | ----- | ---- | ------- | -------- | --------- | ----------- |
| Unix / Linux | v     | v    | v       | v        | v         | v           |
| Windows      | v     | v    | v       | v        | v         | v           |
| Mac          |       |      |         |          |           |             |

#### TODO

Unicode Support :

- [ ] Unix / Linux
- [v] Windows
- [ ] Mac

---

### Installation

require :

- cmake
- c/c++ compiler

```shell
npm install waait-sync
```

---

### Examples

#### uwait

```ts
import { uwait } from "waait-sync";

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

