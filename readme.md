### Cross-Platform sleepSync

|              | uwait | wait | waitKey | waitLine | waitEnter | waitConfirm |
| ------------ | ----- | ---- | ------- | -------- | --------- | ----------- |
| Unix / Linux | v     | v    | v       | v        | v         | v           |
| Windows      | v     | v    | v       | v        | v         | v           |
| Mac          |       |      |         |          |           |             |

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
    uwait(333); // wait 333 μs.
}
```

#### wait

```ts
import { wait } from "waait-sync";

for (let i = 0; i < 10; i++) {
    console.log(i);
    wait(333); // wait 333 ms.
}
```

#### waitKey

```ts
import { waitKey } from "waait-sync";

for (let i = 0; i < 10; i++) {
    console.log(i);
    waitKey(27); // wait ESC(ascii 27).
}
```

#### waitLine

```ts
import { waitLine } from "waait-sync";

for (let i = 0; i < 10; i++) {
    console.log(i);
    waitLine("Hello, World!"); // wait "Hello, World!"
}
```

#### waitEnter

```ts
import { waitEnter } from "waait-sync";

for (let i = 0; i < 10; i++) {
    console.log(i);
    waitEnter();
}
```

#### waitConfirm

```ts
import { waitConfirm } from "waait-sync";

for (let i = 0; i < 10; i++) {
    console.log(i);

    console.log("stop? y/n");
    if (waitConfirm("y", "n")) break;
}
```

