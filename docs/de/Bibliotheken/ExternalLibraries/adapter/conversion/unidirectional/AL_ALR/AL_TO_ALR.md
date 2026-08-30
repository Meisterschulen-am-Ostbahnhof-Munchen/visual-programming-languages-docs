# AL_TO_ALR

![AL_TO_ALR](./AL_TO_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_TO_ALR** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen AL‑Adapter (LWORD) auf einen unidirektionalen ALR‑Adapter (LREAL) abbildet. Er nutzt intern den Baustein `F_LWORD_TO_LREAL`.

> **⚠️ Achtung — keine numerische Wertumwandlung:** `LWORD` ist ein Bit-String-Typ (kein Integer mit Vorzeichen-Semantik), und `F_LWORD_TO_LREAL` reinterpretiert im FORTE-Kern lediglich das 64-Bit-Muster als IEEE754-`LREAL` (Bit-Kopie) — dieselbe Falle wie bei [`AD_TO_AR`](../AD_AR/AD_TO_AR.md) (DWORD→REAL), nur mit den 64-Bit-Pendants. Ein roher Zähler- oder Analogwert wird dadurch **nicht** zum entsprechenden LREAL-Zahlenwert, sondern zu einer bedeutungslosen Zahl. Für eine echte numerische Umwandlung: zweistufig über `AL_TO_AULI` (Bit-Reinterpretation LWORD→ULINT, hier gültig, da beide dieselbe 64-Bit-Darstellung eines vorzeichenlosen Integers teilen) gefolgt von `AULI_TO_ALR` (echter numerischer Cast) — dasselbe Muster wie [`AD_TO_AR_NUM`](../AD_AR/AD_TO_AR_NUM.md) für den 32-Bit-Fall.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Das für die Auslösung der Konvertierung erforderliche Ereignis wird über den Socket **AL_IN** (Typ `AL`) bereitgestellt. Dieses Ereignis (E1) wird intern mit dem `REQ`-Eingang des Konvertierungsbausteins verbunden.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Das Abschlussereignis der Konvertierung wird über den Plug **ALR_OUT** (Typ `ALR`) ausgegeben. Das Ereignis (E1) des internen Bausteins (`CNF`) wird an den Ausgangsadapter weitergeleitet.

### **Daten-Eingänge**

Der FB besitzt keine direkten Daten-Eingänge. Der zu konvertierende LWORD‑Wert wird über den Socket **AL_IN** (Daten-Signal D1) bereitgestellt und an den `IN`-Eingang des Konvertierungsbausteins übergeben.

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten-Ausgänge. Der konvertierte LREAL‑Wert wird über den Plug **ALR_OUT** (Daten-Signal D1) ausgegeben; er stammt vom `OUT`-Ausgang des internen Bausteins.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **AL_IN** | Socket (Eingang) | `adapter::types::unidirectional::AL` | LWORD‑Adapter, der das Eingangssignal (LWORD) und ein Auslöseereignis bereitstellt. |
| **ALR_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::ALR` | LREAL‑Adapter, der das konvertierte Signal (LREAL) und ein Bestätigungsereignis ausgibt. |

## Funktionsweise

`F_LWORD_TO_LREAL` reinterpretiert das 64-Bit-Muster des LWORD als IEEE754-`LREAL` (Bit-Kopie), es findet **keine** Zahlenwert-Konvertierung statt. Der Baustein arbeitet in einem einfachen ereignisgesteuerten Ablauf:

1. Ein eingehendes Ereignis am Socket **AL_IN.E1** wird an den `REQ`-Eingang des internen Funktionsblocks `F_LWORD_TO_LREAL` weitergeleitet.
2. Gleichzeitig wird der Datenwert von **AL_IN.D1** (LWORD) an den `IN`-Eingang des Konverters übergeben.
3. Der interne FB führt die Umwandlung `LWORD → LREAL` durch.
4. Nach Abschluss der Konvertierung wird das Ereignis `CNF` an den Plug **ALR_OUT.E1** gesendet.
5. Der konvertierte LREAL‑Wert wird auf **ALR_OUT.D1** ausgegeben.

Die gesamte Verarbeitung erfolgt innerhalb eines Taktzyklus (keine Blockierung).

## Technische Besonderheiten

- **Adapter‑basierte Schnittstelle**: Der FB nutzt ausschließlich unidirektionale Adapter (`AL` und `ALR`). Dies ermöglicht eine lose Kopplung zwischen Sender und Empfänger sowie eine einfache Wiederverwendung in verschiedenen Systemarchitekturen.
- **⚠️ Bit-Reinterpretation statt Zahlenwert-Umwandlung**: Siehe Warnhinweis in der Einleitung — betrifft alle Bit-String-Quelltypen beim Umwandeln in `AR`/REAL oder `ALR`/LREAL; der einzige weitere Fall in dieser Bibliothek ist [`AD_TO_AR`](../AD_AR/AD_TO_AR.md) (DWORD→REAL).
- **Durchgereichte Ereignissteuerung**: Der Baustein führt keine interne Zustandslogik aus; er leitet Ereignisse und Daten transparent weiter. Die Laufzeit des Aufrufs entspricht der Ausführungszeit des internen Konverters.

## Zustandsübersicht

Der zusammengesetzte Baustein selbst besitzt **keine eigenen Zustände**. Die Verarbeitung wird vollständig durch den intern verwendeten Funktionsblock `F_LWORD_TO_LREAL` gesteuert, der folgendes minimales Zustandsverhalten aufweist:

- **IDLE**: Warten auf ein `REQ`-Ereignis.
- **CONVERT**: Ausführen der Konvertierung (unmittelbar nach `REQ`).
- **SEND**: Ausgeben des `CNF`-Ereignisses und des konvertierten Werts.

Da der innere FB in einem einzigen Ausführungsschritt arbeitet, sind die Zustände nicht von außen beobachtbar.

## Anwendungsszenarien

- **Bitmuster-Weitergabe**: `AL_IN` liefert bereits ein Bitmuster, das als LREAL interpretiert werden soll (z. B. serialisierte Double-Rohdaten aus einem Feldbus/Protokoll).
- **NICHT geeignet** für rohe Zähler-, Analog- oder sonstige Ganzzahlwerte, die als derselbe Zahlenwert in LREAL vorliegen sollen — dafür `AL_TO_AULI` + `AULI_TO_ALR` verwenden.

## Vergleich mit ähnlichen Bausteinen

- **`AL_TO_AULI` + `AULI_TO_ALR`** (numerisch, LWORD→ULINT→LREAL): der sichere Ersatz, wenn tatsächlich ein Zahlenwert gemeint ist.
- **`ALI_TO_ALR`/`AULI_TO_ALR`** (LINT/ULINT→LREAL): bereits numerisch korrekt, da ihre Quelltypen `ANY_INT` (nicht `ANY_BIT`) sind — kein Trap.
- **[`AD_TO_AR`](../AD_AR/AD_TO_AR.md)** (DWORD→REAL): dieselbe Bit-Reinterpretations-Falle, nur mit den 32-Bit-Pendants.

## Fazit

`AL_TO_ALR` bietet eine kompakte Lösung, um ein LWORD-Bitmuster über Adapter-Schnittstellen als LREAL bereitzustellen — **aber keine numerische Wertumwandlung**. Für rohe Zähler- oder Analogwerte, die als derselbe Zahlenwert in LREAL vorliegen sollen, `AL_TO_AULI` + `AULI_TO_ALR` verwenden.

---

### 📖 Hintergrund

* [Numerisch vs. bitweise: Die Konvertierungs-Falle in FORTE](../Numerisch_vs_Bitweise.md)
