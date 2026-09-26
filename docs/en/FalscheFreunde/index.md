# ⚠️ False Friends (IEC 61499 / 4diac)

In event-driven function block programming according to **IEC 61499**, several standard function blocks behave differently than developers accustomed to traditional cyclic PLC programming (IEC 61131-3) would expect. These blocks are referred to as **"False Friends"**: they carry familiar names, but without considering event-driven execution logic, they lead to subtle bugs, unexpected startup behavior, or state deadlocks.

This chapter documents typical pitfalls, explains their root causes within the Event Execution Control Chart (ECC), and presents recommended remedies.

---

## 1. The `NOT` Block (or `F_NOT`)

### ❌ The Problem

In classic PLC programming (IEC 61131-3), negation is evaluated statically: `OUT := NOT IN`. If input `IN = FALSE`, output `OUT` is immediately `TRUE`.

In **IEC 61499**, however, data values are evaluated **only when an event arrives at the `REQ` input**.
Upon system startup or deployment, all memory locations default to zero/`FALSE`:
* `IN = FALSE`
* `OUT = FALSE`

As long as **no first event** has arrived at `REQ` after startup, the execution algorithm has never run. Consequently, immediately after startup, **both the input and the output are `FALSE`**!
If output `OUT` is used directly for permission or control logic (e.g., active-low / fail-safe logic), the system remains stuck in an uninitialized block state.

```text
System Startup / Before First Event:
IN  = FALSE
OUT = FALSE  ❌ (Contradicts NOT(FALSE) = TRUE)

After First REQ Event:
IN  = FALSE
OUT = TRUE   ✅ (Only now correct)
```

### ✅ Solution: `NOT_INIT` or `AX_NOT_INIT` (or Startup Event Triggering)

For signals that require a defined state upon system startup, use function blocks with an explicit initialization event:
* **`NOT_INIT`** / **`AX_NOT_INIT`**: These blocks feature an `INIT` event (triggered at startup e.g. via `E_RESTART`). Upon receiving `INIT`, the signal is immediately negated and output `OUT` is pre-seeded with the mathematically correct value (`TRUE` when `IN = FALSE`).
* **Initial REQ Event**: Ensure that a first event is triggered explicitly at system startup via an initialization routine.

---

## 2. Bistable Elements `E_RS` and `E_SR`

### ❌ The Problem

Developers expect a flip-flop to react deterministically to set (`S`) and reset (`R`) signals regardless of its current state.

Standard IEC 61499 blocks like **`E_RS`** and **`E_SR`** begin after deployment in the uninitialized `START` state of their Event Execution Control Chart (ECC). In this `START` state, many standard implementations react **exclusively to an `S` (Set) event**:
* Arrival of `S`: The block transitions to state `SET`, sets `Q := TRUE`, and emits `EO`.
* Arrival of `R` in `START` state: If a **`R` (Reset) event** arrives as the first event after startup, the block remains in `START` or ignores the event. The flip-flop fails to become operational and does not respond to reset commands as expected.

```text
START State (after deployment):
Receiving 'S' ──► State SET (Q := TRUE)  ✅
Receiving 'R' ──► Remains in START / ignored ❌
```

### ✅ Solution: `E_RS_SYM` and `E_SR_SYM` (or `E_RS_SYM_INIT`)

Use the **symmetric variants** (*Symmetric Start-up Behavior*) instead:
* **`E_RS_SYM` / `E_SR_SYM`**: Right from the initial `START` state, **both `S` and `R`** lead to well-defined follow-up states (`SET` and `RESET` respectively). An incoming reset event at startup immediately transitions the block cleanly to `RESET` (`Q := FALSE`, `EO`).
* **`E_RS_SYM_INIT` / `E_SR_SYM_INIT`**: Provide additional explicit startup value initialization via an `INIT` event and `Q_INIT` data input.

---

## 3. Overview & Recommendations

| Function Block | "False Friend" Due To | Recommended Alternative / Remedy |
| :--- | :--- | :--- |
| **`NOT` / `F_NOT`** | Input and output are both `FALSE` before the first `REQ` event. | **`NOT_INIT`**, **`AX_NOT_INIT`**, or explicit startup event triggering |
| **`E_RS` / `E_SR`** | Only an `S` event activates the block from `START` state; `R` at startup is ignored. | **`E_RS_SYM`**, **`E_SR_SYM`**, or **`E_RS_SYM_INIT`** |

---

## 🔮 More to Follow...

This list of "False Friends" will be continuously expanded with additional real-world pitfalls of event-driven programming (e.g., unwired event outputs, edge vs. level evaluation, timing behavior without cycle guarantees).
