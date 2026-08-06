# Type Compatibility in 4diac IDE (Data Connections)
The rules for allowed data connections are based on the principle:
**"Target must be able to accept Source"**.
## Central Files in the Codebase
| File | Purpose |
|-------|-------|
| `plugins/org.eclipse.fordiac.ide.model/src/org/eclipse/fordiac/ide/model/data/impl/DataTypeAnnotations.java` | Defines `isAssignableFrom(DataType other)` for each IEC 61131-3 type |
| `plugins/org.eclipse.fordiac.ide.model/src/org/eclipse/fordiac/ide/model/validation/LinkConstraints.java:200` | Tests connections with `targetType.isAssignableFrom(sourceType)` |
| `tests/.../datatype/helper/ElementaryDataTypeCompatibilityTest.java` | Complete test matrix of all implicit assignments |

## Basic Principle

A connection from **Source** → **Target** is allowed if:

```java
targetType.isAssignableFrom(sourceType)
```
This means: the target type must be equal to or greater than the source type.

## Integer Types

### Signed

| Source → | SINT | INT | DINT | LINT |
|----------|:----:|:---:|:----:|:----:|
**SINT** | ✓ | ✓ | ✓ | ✓ |
**INT** | ✗ | ✓ | ✓ | ✓ |
**DINT** | ✗ | ✗ | ✓ | ✓ |
**LINT** | ✗ | ✗ | ✗ | ✓ |

## Unsigned

| Source → | USINT | UINT | UDINT | ULINT |
|----------|:-----:|:----:|:-----:|:-----:|
**USINT** | ✓ | ✓ | ✓ | ✓ |
**UINT** | ✗ | ✓ | ✓ | ✓ |
**UDINT** | ✗ | ✗ | ✓ | ✓ |
**ULINT** | ✗ | ✗ | ✗ | ✓ |

> **Important:** There is **no** implicit conversion between Signed and Unsigned.

> `INT` → `UINT` is not allowed.

## Floating-Point Types

| Source → | REAL | LREAL |
|----------|:----:|:-----:|
| **REAL** | ✓ | ✓ |
| **LREAL** | ✗ | ✓ |

REAL and LREAL also accept certain integer types:

- **REAL** accepts: `INT`, `SINT`, `UINT`, `USINT`
- **LREAL** accepts: `DINT`, `INT`, `SINT`, `UDINT`, `UINT`, `USINT`, `REAL`

## Bit Types

| Source → | BOOL | BYTE | WORD | DWORD | LWORD |
|----------|:----:|:----:|:----:|:-----:|:-----:|
**BOOL** | ✓ | ✓ | ✓ | ✓ | ✓ |
**BYTE** | ✗ | ✓ | ✓ | ✓ | ✓ |
**WORD** | ✗ | ✗ | ✓ | ✓ | ✓ |
**DWORD**| ✗ | ✗ | ✗ | ✓ | ✓ |
**LWORD**| ✗ | ✗ | ✗ | ✗ | ✓ |

## Characters and Strings

| Source → | CHAR | WCHAR | STRING | WSTRING |
|----------|:----:|:-----:|:------:|:-------:|
| **CHAR** | ✓ | ✗ | ✓ | ✗ |
| **WCHAR**| ✗ | ✓ | ✗ | ✓ |

## Time and Date Types

Long types also accept short variants:

- **LTIME** ← `TIME`
- **LDATE** ← `DATE`
- **LTOD** ← `TOD`
- **LDT** ← `DT`

## Summary of Rules

1. **Width Rule:** A smaller type may be concatenated with a larger type (e.g., `UINT` → `UDINT`).

2. **No Narrowing:** A larger type cannot be joined to a smaller type (e.g., `UDINT` → `UINT` is forbidden).

3. **Sign Boundary:** Signed and unsigned integers are not compatible (e.g., `INT` → `UINT` is forbidden).

4. **Boolean Special Rule:** `BOOL` can be joined to any bit type (`BYTE`, `WORD`, `DWORD`, `LWORD`).

## Obsolete Conversions & F_MOVE

### 1. Deprecated Conversion Modules
All old identity conversion modules from the folder `convert-1.0.0` (such as `BOOL2BOOL`, `INT2INT`, `DINT2DINT`, `REAL2REAL`, `STRING2STRING`, etc.) are **deprecated** and must no longer be used.

### 2. Using `F_MOVE`

To copy or forward values of the same type, the generic function block `F_MOVE` (`iec61131::selection::F_MOVE`) must be used instead.

### 3. Configuring `F_MOVE`
Since `F_MOVE` is generic, it must be configured in XML network files using the attribute `DataType` to specify the desired target data type.

**Example configuration in the XML:**

```xml
<FB Name="MeinFMove" Type="iec61131::selection::F_MOVE">
<Attribute Name="DataType" Value="BOOL"/> <!-- Hier Datentyp konfigurieren -->
</FB>
```

Without this attribute or with an empty value, the function block is invalid and will fail validation.

## Explicit Type Conversions (Casting) in ST & FB Networks

If an assignment (in ST) or a connection (in the FB network) is not implicitly allowed (see matrix above), an explicit conversion must be performed:

* **In Structured Text (ST):** Use a conversion function of the form `[SOURCE_TYPE]_TO_[TARGET_TYPE]` (e.g., `DINT_TO_UDINT`).
* **In the graphical FB network:** Insert the corresponding conversion function block (e.g., block `DINT_TO_UDINT`) between the output and input.
### ⚠️ Important Special Case: Bit Strings to Numeric Types (reinterpret_cast)

In FORTE / 4diac, conversions of bit strings (such as `DWORD`, `WORD`, `BYTE`) to numeric types (`REAL`, `INT`, `DINT`, etc.) are performed at the bit level **`reinterpret_cast`**. This means that the bit patterns are copied directly without adjusting the mathematical value. This applies equally to ST function calls and graphical conversion blocks.

Scenario A: A numeric value (e.g., UDINT) is stored in the DWORD.

If a numeric integer value (e.g., 123) is stored in a `DWORD` and this value is to be output as a floating-point number (`REAL`):

* **Incorrect:**
* *In ST:* `real_var := DWORD_TO_REAL(dword_var);`
* *In the FB network:* Direct connection via the conversion block `DWORD_TO_REAL`.
* *Explanation:* This copies the bits of 123 directly into the float bit pattern. According to IEEE-754, this is interpreted as an extremely small, almost infinitely close zero, which is mathematically incorrect.
* **Correct (double conversion):**
  * *In ST:*
    ```pascal
    real_var := UDINT_TO_REAL(DWORD_TO_UDINT(dword_var));
    ```

  * *In the FB network:* Sequential insertion of two conversion modules:
    `[DWORD-Ausgang]` $\rightarrow$ `[DWORD_TO_UDINT]` $\rightarrow$ `[UDINT_TO_REAL]` $\rightarrow$ `[REAL-Eingang]`.

  * *Explanation:* `DWORD_TO_UDINT` copies the bit pattern (123 remains 123 as a UDINT). `UDINT_TO_REAL` then performs the actual mathematical conversion to the floating-point number `123.0`.

Scenario B: An IEEE-754 float bit pattern is already stored in the DWORD.

If `DWORD` directly contains the raw bit pattern of a floating-point number (e.g., read in via a Modbus register or a network connection):

* **Correct:**
  * *In ST:* `real_var := DWORD_TO_REAL(dword_var);`
  * *In the FB network:* Insert the conversion block `DWORD_TO_REAL`.
  * *Explanation:* Here, the direct cast via `reinterpret_cast` is exactly what's needed to interpret the raw bits directly as a floating-point number.

## Type Conversions (Casting)

### Direct Bit-String-to-Floating-Point Conversions

The following direct conversions are **not defined** in IEC 61131-3 / IEC 61499:

- `BYTE_TO_REAL` → **not defined**
- `WORD_TO_REAL` → **not defined**

Instead, you must convert using the appropriate unsigned integer type:

| Source | Destination | Correct Conversion |

|--------|------|---------------------|
| BYTE | REAL | `BYTE` → `USINT` → `REAL` |
| WORD | REAL | `WORD` → `UINT` → `REAL` |
| DWORD | REAL | `DWORD` → `UDINT` → `REAL` |
| LWORD | LREAL | `LWORD` → `ULINT` → `LREAL` |

### DWORD_TO_REAL, LWORD_TO_LREAL = reinterpret_cast

**Important:** `DWORD_TO_REAL` and `LWORD_TO_LREAL` in 4diac correspond to `reinterpret_cast` in C++. This means:

- The bit representation is interpreted directly as REAL
- **No numerical conversion** takes place
- Example: `16#41480000` as a DWORD becomes `12.5` as REAL (same bit representation)

This is generally **not** the desired behavior for numerical conversions!

### The 16,777,216 Problem (REAL Precision Loss)

REAL only has 32 bits and can therefore only represent **7 decimal places** precisely.

When converting large unsigned values, accuracy is lost starting at **16,777,216** (2^24):

```iecst
UDINT#16777216  →  UDINT_TO_REAL()  →  REAL#16777216.0  →  Correct (2^24)
UDINT#16777217  →  UDINT_TO_REAL()  →  REAL#16777216.0  →  Precision loss (rounding)
```

**Solution:** For values ≥ 16,777,216, use `LREAL` instead of `REAL`:

```iecst
UDINT#16777217  →  UDINT_TO_LREAL()  →  LREAL#16777217.0  ✓
```

This applies in particular to:

- UDINT (32-bit) conversions to REAL (or DWORD after conversion to UDINT)
- ULINT (64-bit) conversions to LREAL (or LWORD after conversion to ULINT; with LREAL, the loss of precision only occurs from 2^53 onwards)

**Rule of thumb:** All FIELDBUS signal blocks for DWORD, UDINT, LWORD, and ULINT should use `LREAL` as the output type.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
