const addon = require("bindings")("sleepSync");

/**
 * Suspends the execution until the time-out interval elapses.
 *
 * @warn Never use with async, this will pause sync also.
 * @param timeout >Time to wait (in micro-seconds)
 */
export function uwait(timeout: number): void {
    if (0 < timeout) addon.uwait(timeout);
}

/**
 * Suspends the execution until the time-out interval elapses.
 *
 * @warn Never use with async, this will pause sync also.
 * @param timeout >Time to wait (in milli-seconds)
 */
export function wait(timeout: number): void {
    if (0 < timeout) addon.wait(timeout);
}

/**
 * Suspends the execution until the desired key is pressed.
 * Returns true if the key is pressed.
 * Returns false if the timeout has passed.
 *
 * @warn Never use with async, this will pause sync also.
 * @param expect >ASCII number of the key to wait until pressed (If undefined: any key)
 * @param timelimit >Maximum time to wait (in milli-seconds, If undefined: no timeout)
 */
export function waitKey(expect?: number, timelimit?: number): boolean {
    return addon.waitKey(expect, timelimit);
}

/**
 * Suspends the execution until the desired line is typed.
 * Returns true if the key is pressed.
 * Returns false if the timeout has passed.
 *
 * @warn Never use with async, this will pause sync also.
 * @param expect >string for wait.
 * @param timelimit >Maximum time to wait (in milli-seconds, If undefined: no timeout)
 */
export function waitLine(expect: string, timelimit?: number): boolean {
    return addon.waitLine(expect, timelimit);
}

/**
 * Suspends the execution until the enter is pressed.
 * Returns true if the key is pressed.
 * Returns false if the timeout has passed.
 *
 * @warn Never use with async, this will pause sync also.
 * @param timelimit >Maximum time to wait (in milli-seconds, If undefined: no timeout)
 */
export function waitEnter(timelimit?: number): void {
    addon.waitEnter(timelimit);
}

/**
 * Suspends the execution until the user confirms.
 * Returns true if the user enters an acceptance string.
 * Returns false if the user enters a rejection string or a timeout has passed.
 *
 * @warn Never use with async, this will pause sync also.
 * @param ystr >string for accept.
 * @param nstr >string for reject. (If undefined: )
 * @param timelimit >Maximum time to wait (in milli-seconds, If undefined: no timeout)
 */
export function waitConfirm(ystr: string, nstr?: string, timelimit?: number): boolean {
    return addon.waitConfirm(ystr, nstr, timelimit);
}
