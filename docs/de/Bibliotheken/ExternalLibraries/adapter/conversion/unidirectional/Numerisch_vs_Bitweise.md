# Numerisch vs. bitweise: Die Konvertierungs-Falle in FORTE

* * * * * * * * * *
## Einleitung

Alle Bausteine in diesem Ordner (`AB_TO_AR`, `AD_TO_ADI`, `AI_TO_AR`, usw.) sowie die zugrunde liegenden Standard-Funktionsblöcke `iec61131::conversion::F_X_TO_Y` (Teil der 4diac-IDE-Standardbibliothek, nicht in diesem Repository vendored) wandeln einen Wert von einem IEC-61131-Datentyp in einen anderen um. Für einen Teil dieser Kombinationen ist das eine **echte Zahlenwert-Umwandlung**; für einen anderen Teil ist es eine **reine Bit-Reinterpretation**, bei der der Zahlenwert bewusst ignoriert und stattdessen das rohe Bitmuster übernommen wird. Wer den Unterschied nicht kennt, produziert leicht einen stillen, schwer zu findenden Bug — siehe `AD_TO_AR_TODO.md` im Quell-Repository für den konkreten Fall, der diese Seite ausgelöst hat.

## Die vier Typkategorien

IEC 61131-3 unterscheidet vier relevante Kategorien:

| Kategorie | Typen | Bedeutung |
|---|---|---|
| **ANY_BIT** | `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD` | reine Bitmuster ohne eigene Zahlenwert-Semantik |
| **ANY_INT** (vorzeichenbehaftet) | `SINT`, `INT`, `DINT`, `LINT` | Ganzzahlen mit Vorzeichen |
| **ANY_INT** (vorzeichenlos) | `USINT`, `UINT`, `UDINT`, `ULINT` | Ganzzahlen ohne Vorzeichen |
| **ANY_REAL** | `REAL`, `LREAL` | IEEE754-Gleitkommazahlen |

Die Adapter-Präfixe in diesem Ordner entsprechen: `AB`=BYTE, `AW`=WORD, `AD`=DWORD, `AL`=LWORD, `AX`=BOOL, `AS`=SINT, `AI`=INT, `ADI`=DINT, `ALI`=LINT, `AUS`=USINT, `AUI`=UINT, `AUDI`=UDINT, `AULI`=ULINT, `AR`=REAL, `ALR`=LREAL.

## Die Umwandlungsmatrix

Verifiziert im FORTE-Kern (`core/include/forte/datatypes/forte_any.h`, `CIEC_ANY::cast<U,T>`, sowie `forte_real.cpp`/`forte_lreal.cpp`, `CIEC_REAL::castRealData`) — dieselbe Logik hinter jedem `F_X_TO_Y`-Baustein und jedem Adapter-Wrapper in diesem Ordner:

| Quelle ＼ Ziel | → ANY_BIT | → ANY_INT | → ANY_REAL |
|---|---|---|---|
| **ANY_BIT** (außer BOOL) | Bit-Kopie (strukturell, kein Zahlenwert) | Bit-Reinterpretation — **werterhaltend**, wenn Ziel gleich breit oder breiter ist; schneidet sonst ab | ⚠️ **Bit-Reinterpretation — KEIN Zahlenwert!** IEEE754-Fehlinterpretation |
| **BOOL** | Paritäts-/LSB-Test | numerisch (0/1) | numerisch (0.0/1.0) — Sonderfall, siehe unten |
| **ANY_INT** | speichert das Bitmuster (erwartetes Verhalten für ein Bit-String-Ziel) | numerisch (Vorzeichenerweiterung/Nullerweiterung sicher, Verengung kann abschneiden) | **numerisch** (korrekter Cast) |
| **ANY_REAL** | Bit-Extraktion (beabsichtigt, z. B. Serialisierung via `F_REAL_TO_DWORD`) | numerisch (Rundung, `llrint`) | numerisch (Auf-/Abrunden der Genauigkeit) |

**Die einzige echte Falle** ist also die Zelle **ANY_BIT (außer BOOL) → ANY_REAL** (rot markiert): `BYTE`/`WORD`/`DWORD`/`LWORD` als Quelle einer Umwandlung nach `REAL`/`LREAL`. In dieser Bibliothek betrifft das konkret zwei Bausteine:

- [`AD_TO_AR`](./AD_AR/AD_TO_AR.md) (DWORD→REAL) — sicherer Ersatz: [`AD_TO_AR_NUM`](./AD_AR/AD_TO_AR_NUM.md)
- [`AL_TO_ALR`](./AL_ALR/AL_TO_ALR.md) (LWORD→LREAL) — sicherer Ersatz: `AL_TO_AULI` + `AULI_TO_ALR`

(Es gibt in dieser Bibliothek keine `AB_TO_AR`/`AB_TO_ALR`/`AW_TO_AR`/`AW_TO_ALR`-Paare — nur breitenpassende Bit↔Real-Kombinationen wurden als Adapter angeboten.)

**Warum ist BOOL→REAL sicher, obwohl BOOL zu ANY_BIT gehört?** FORTE behandelt BOOL beim Cast nach REAL als expliziten Sonderfall (`case e_BOOL: setTFLOAT(...)` statt der generischen Bit-String-Kopie) — der einzige Ausnahmefall in der Matrix.

## Warum ist ANY_BIT→ANY_REAL überhaupt so implementiert?

Nicht aus Willkür: Für Bit-String-Ziele (`ANY_BIT`→`ANY_BIT`) und für den Rückweg `ANY_REAL`→`ANY_BIT` ist die Bit-Reinterpretation genau das gewünschte, dokumentierte Verhalten — z. B. um das IEEE754-Bitmuster eines REAL für die Übertragung in ein DWORD zu packen (`F_REAL_TO_DWORD`) und später mit `AD_TO_AR` wieder auszupacken. Die Krux ist die **Verwechslungsgefahr**: derselbe Mechanismus wird fälschlich auch dann verwendet, wenn eigentlich ein roher Zähler- oder Analogwert (kein serialisiertes Bitmuster) numerisch nach REAL soll.

## Praktische Faustregel

- **Kommt der Wert aus einem `F_REAL_TO_X`/`F_X_TO_REAL`-Roundtrip oder einer Feldbus-/Protokoll-Deserialisierung, bei der explizit Bitmuster übertragen werden?** → Bit-Reinterpretation ist korrekt (`AD_TO_AR`, `AL_TO_ALR`).
- **Ist der Wert ein roher Zähler-, Analog- oder sonstiger Ganzzahlwert, der als derselbe Zahlenwert in REAL vorliegen soll?** → Numerische Variante verwenden (`AD_TO_AR_NUM`, oder allgemein: zweistufig über den passenden `ANY_INT`-Zwischentyp, z. B. `AD_TO_AUDI` → `AUDI_TO_AR`).
- **Alle anderen Zellen der Matrix** sind entweder eindeutig numerisch oder eindeutig strukturell (Bit-Operation) — ohne die versteckte Fehlinterpretations-Gefahr der ANY_BIT→ANY_REAL-Zelle. Jeder Baustein in diesem Ordner trägt einen kurzen Hinweis dazu in seinem Abschnitt "Technische Besonderheiten".

## Betrifft auch die Standard-Konvertierungsbausteine

Die hier dokumentierten Adapter-Bausteine (`AD_TO_AR` etc.) sind dünne Wrapper um die Standard-4diac-Funktionsblöcke `iec61131::conversion::F_X_TO_Y` (z. B. `F_DWORD_TO_REAL`). Diese Standardbausteine sind Teil der 4diac-IDE-Distribution selbst (nicht in diesem Repository vendored) und unterliegen exakt derselben Matrix — `F_DWORD_TO_REAL`, `F_WORD_TO_REAL`, `F_BYTE_TO_LREAL` usw. sind ebenso Bit-Reinterpretationen, während `F_DINT_TO_REAL`, `F_UDINT_TO_REAL` usw. numerisch korrekt sind.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
