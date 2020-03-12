const addon = require("bindings")("sleepSync");

/**
 * Suspends the execution of the current thread until the time-out interval elapses.
 * If a negative number is given, it does not suspend.
 */
export function sleepSync(ms: number) {
  if (ms <= 0) return;
  addon.sleepSync(ms);
}
