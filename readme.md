### Cross-Platform sleepSync

- [x] Unix / Linux
- [x] Windows
- [ ] Mac

```ts
import { sleepSync } from "sleepSync";

for (let i = 0; i < 10; i++) {
  console.log(i);
  sleepSync(1000); // ms
}
```

---

#### Installation

Install `cmake` first, then.

```shell
npm install sleepSync
```
