# ℹ️ General

This section explains fundamental concepts that are important for programming according to IEC 61131-3 and IEC 61499, as well as for general computer science.
## Identifiers (Naming Conventions)

Names of variables, function blocks, programs, and other elements are called **identifiers**. To ensure clean and portable code, the IEC 61131-3 standard establishes strict rules.
### Basic Rules of the Standard

1. **Character Set:** Identifiers may only consist of letters (A-Z, a-z), digits (0-9), and the underscore (_).
2. **Starting Point:** A name may **not begin with a digit**. It must start with a letter or an underscore.
3. **Spaces:** Spaces are not allowed within a name.
4. **Special Characters:** Umlauts (ä, ö, ü) and special characters ($, %, &, /) are strictly prohibited.
5. **Case Sensitivity:** Standard IEC 61131-3 generally does not distinguish between uppercase and lowercase letters (`Motor_An` is the same as `motor_an`). However, it is good practice to maintain consistent notation.
6. **Reserved Words:** Language keywords (e.g., `IF`, `THEN`, `VAR`, `END_VAR`) may not be used as identifiers.

### Best Practices (Recommendations)

* **Underscores:** Avoid single underscores at the beginning of names, as these are often reserved for internal library functions.
* **Double Underscores:** These are reserved or forbidden in many systems.
* **Clarity:** Names should be self-explanatory. Use `Temperatur_Sensor_1` instead of `T_S1`.
* **Synonyms:**
* **CamelCase:** `MaxTemperatur`
* **SnakeCase:** `Max_Temperatur` (very common in the PLC world)

| Allowed | Forbidden | Reason |
| :--- | :--- | :--- |
| `Maehwerk_An` | `Mähwerk_An` | Special character (ä) |
| `Start_Taster_1` | `1_Start_Taster` | Begins with a digit |
| `Sollwert_Vorgabe` | `Sollwert Vorgabe` | Space |
| `__Internal` | `Internal!` | Special character (!) |

---

## Numbers and Literals

The representation of numbers (binary, hexadecimal, decimal) and the use of literals in code are essential for control programming.

* Detailed information can be found here: **[Numbers and Number Systems ](Zahlen.md)**

---

## 💾 Data Types

Data types define what kind of information a variable can store (e.g., an integer, a floating-point number, or a Boolean value).

* An overview can be found here: **[DataTypes](Datentypen/index.md)**
* Information on generic data types: **[ANYTypes](Datentypen/GenerischeDatentypen/ANY-Typen.md)**
* Which types can be combined: **[TypeCompatibility](Datentypen/Typkompatibilität.md)**

---

## 🚜 Mnemonic: Remember the standard number

If you absolutely cannot remember the number **IEC 61499**, here's a memory aid:

* **[Mnemonic: IEC 61499](Eselsbruecke_IEC61499.md)**
