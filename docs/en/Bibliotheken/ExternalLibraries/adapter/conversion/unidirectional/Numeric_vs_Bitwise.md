# Numeric vs. bitwise: the FORTE conversion trap

* * * * * * * * * *
## Introduction

Every block in this folder (`AB_TO_AR`, `AD_TO_ADI`, `AI_TO_AR`, etc.) as well as the underlying standard function blocks `iec61131::conversion::F_X_TO_Y` (part of the 4diac IDE standard library, not vendored in this repository) convert a value from one IEC 61131 data type to another. For some of these combinations that is a **real numeric value conversion**; for others it is a **pure bit-reinterpretation**, where the numeric value is deliberately ignored and the raw bit pattern is copied instead. Not knowing the difference easily produces a silent, hard-to-find bug — see `AD_TO_AR_TODO.md` in the source repository for the concrete case that triggered this page.

## The four type categories

IEC 61131-3 distinguishes four relevant categories:

| Category | Types | Meaning |
|---|---|---|
| **ANY_BIT** | `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD` | pure bit patterns with no numeric semantics of their own |
| **ANY_INT** (signed) | `SINT`, `INT`, `DINT`, `LINT` | signed integers |
| **ANY_INT** (unsigned) | `USINT`, `UINT`, `UDINT`, `ULINT` | unsigned integers |
| **ANY_REAL** | `REAL`, `LREAL` | IEEE754 floating-point numbers |

The adapter prefixes in this folder correspond to: `AB`=BYTE, `AW`=WORD, `AD`=DWORD, `AL`=LWORD, `AX`=BOOL, `AS`=SINT, `AI`=INT, `ADI`=DINT, `ALI`=LINT, `AUS`=USINT, `AUI`=UINT, `AUDI`=UDINT, `AULI`=ULINT, `AR`=REAL, `ALR`=LREAL.

## The conversion matrix

Verified against the FORTE core (`core/include/forte/datatypes/forte_any.h`, `CIEC_ANY::cast<U,T>`, and `forte_real.cpp`/`forte_lreal.cpp`, `CIEC_REAL::castRealData`) — the same logic behind every `F_X_TO_Y` block and every adapter wrapper in this folder:

| Source ＼ Destination | → ANY_BIT | → ANY_INT | → ANY_REAL |
|---|---|---|---|
| **ANY_BIT** (except BOOL) | bit copy (structural, no numeric meaning) | bit-reinterpretation — **value-preserving** if the destination is same-or-wider width; truncates otherwise | ⚠️ **bit-reinterpretation — NOT a numeric value!** IEEE754 misinterpretation |
| **BOOL** | parity/LSB test | numeric (0/1) | numeric (0.0/1.0) — special case, see below |
| **ANY_INT** | stores the bit pattern (expected behavior for a bit-string destination) | numeric (sign-/zero-extension is safe, narrowing may truncate) | **numeric** (correct cast) |
| **ANY_REAL** | bit extraction (intentional, e.g. serialization via `F_REAL_TO_DWORD`) | numeric (rounding, `llrint`) | numeric (widen/narrow precision) |

**The one genuine trap** is therefore the **ANY_BIT (except BOOL) → ANY_REAL** cell: using `BYTE`/`WORD`/`DWORD`/`LWORD` as the source of a conversion to `REAL`/`LREAL`. In this library that concretely affects two blocks:

- [`AD_TO_AR`](./AD_AR/AD_TO_AR.md) (DWORD→REAL) — safe replacement: [`AD_TO_AR_NUM`](./AD_AR/AD_TO_AR_NUM.md)
- [`AL_TO_ALR`](./AL_ALR/AL_TO_ALR.md) (LWORD→LREAL) — safe replacement: `AL_TO_AULI` + `AULI_TO_ALR`

(There are no `AB_TO_AR`/`AB_TO_ALR`/`AW_TO_AR`/`AW_TO_ALR` pairs in this library — only width-matched bit↔real combinations were offered as adapters.)

**Why is BOOL→REAL safe even though BOOL belongs to ANY_BIT?** FORTE treats BOOL as an explicit special case when casting to REAL (`case e_BOOL: setTFLOAT(...)` instead of the generic bit-string copy) — the one exception in the matrix.

## Why is ANY_BIT→ANY_REAL implemented this way at all?

It's not arbitrary: for bit-string destinations (`ANY_BIT`→`ANY_BIT`) and for the reverse direction `ANY_REAL`→`ANY_BIT`, bit-reinterpretation is exactly the intended, documented behavior — e.g. to pack a REAL's IEEE754 bit pattern into a DWORD for transport (`F_REAL_TO_DWORD`) and later unpack it again with `AD_TO_AR`. The pitfall is **confusion**: the same mechanism gets used by mistake when a raw counter or analog value (not a serialized bit pattern) is actually meant to become that numeric value in REAL.

## Practical rule of thumb

- **Does the value come from an `F_REAL_TO_X`/`F_X_TO_REAL` round trip, or from fieldbus/protocol deserialization where bit patterns are explicitly transported?** → Bit-reinterpretation is correct (`AD_TO_AR`, `AL_TO_ALR`).
- **Is the value a raw counter, analog, or other integer value meant to carry the same numeric value in REAL?** → Use the numeric variant (`AD_TO_AR_NUM`, or in general: chain through the matching `ANY_INT` intermediate type, e.g. `AD_TO_AUDI` → `AUDI_TO_AR`).
- **Every other cell of the matrix** is either unambiguously numeric or unambiguously structural (a bit operation) — without the hidden misinterpretation risk of the ANY_BIT→ANY_REAL cell. Every block in this folder carries a short note about this in its "Technical Details" section.

## Also affects the standard conversion blocks

The adapter blocks documented here (`AD_TO_AR` etc.) are thin wrappers around the standard 4diac function blocks `iec61131::conversion::F_X_TO_Y` (e.g. `F_DWORD_TO_REAL`). These standard blocks are part of the 4diac IDE distribution itself (not vendored in this repository) and are subject to exactly the same matrix — `F_DWORD_TO_REAL`, `F_WORD_TO_REAL`, `F_BYTE_TO_LREAL` etc. are likewise bit-reinterpretations, while `F_DINT_TO_REAL`, `F_UDINT_TO_REAL` etc. are numerically correct.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
