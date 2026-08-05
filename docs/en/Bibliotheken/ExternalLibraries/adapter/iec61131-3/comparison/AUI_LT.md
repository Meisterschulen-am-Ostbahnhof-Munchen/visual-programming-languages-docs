# AUI_LT
![AUI_LT](./AUI_LT.svg)

* * * * * * * * * *
## Introduction
The function block `AUI_LT` performs a less-than comparison (`<`) between two input values. It is accessed via adapter interfaces and is suitable for use in component-based automation systems according to IEC 61131-3. The block performs the comparison asynchronously and outputs the result as a Boolean value via an output adapter.
## Interface Structure

### **Event Inputs**

| Name | Description |

|------------|--------------|

| IN1.E1 | Event at socket adapter IN1; triggers the comparison as soon as a new value is present at IN1. |

| IN2.E1 | Event at socket adapter IN2; triggers the comparison as soon as a new value is present at IN2. |

### **Event Outputs**

| Name | Description |

|------------|--------------|

| OUT.E1 | Event at plug adapter OUT; signals that a valid result is present at OUT.D1 after a comparison. |

### **Data Inputs**

| Name | Description |

|------------|--------------|

| IN1.D1 | First value of the comparison (ANY_BIT compatible). |

| IN2.D1 | Second value of the comparison (ANY_BIT compatible). |

### **Data Outputs**

| Name | Description |

|------------|--------------|

| OUT.D1 | Comparison result: `true`, if IN1.D1 < IN2.D1; sonst `false`. |

### **Adapter**

| Bezeichnung | Typ               | Richtung | Beschreibung |
|------------|-------------------|----------|--------------|
| IN1        | AUI (unidirectional) | Socket   | Eingangsadapter für den ersten Wert und dessen Ereignis. |
| IN2        | AUI (unidirectional) | Socket   | Eingangsadapter für den zweiten Wert und dessen Ereignis. |
| OUT        | AX (unidirectional) | Plug     | Ausgangsadapter für das Vergleichsergebnis und das zugehörige Ereignis. |

## Funktionsweise

Der `AUI_LT`-Baustein ist als Composite-FB realisiert. Intern wird ein einzelner `F_LT`-Funktionsblock (aus der IEC 61131-3 Vergleichsbibliothek) verwendet.

- Die **Ereignis-Eingänge** `IN1.E1` und `IN2.E1` sind beide mit dem `REQ`-Eingang des internen `F_LT` verbunden. Sobald an einem der beiden Adapter ein Ereignis eintrifft, wird der Vergleich angestoßen.
- Die **Datenwerte** `IN1.D1` und `IN2.D1` werden direkt an die entsprechenden Eingänge `IN1` und `IN2` des `F_LT` weitergeleitet.
- Nach Abschluss der Berechnung signalisiert der `F_LT` über seinen Ausgang `CNF` das Ereignis `OUT.E1` und stellt das Vergleichsergebnis am Datenausgang `OUT.D1` bereit.

Der Vergleich erfolgt nach der Logik: **IN1.D1 < IN2.D1 ⇒ OUT.D1 = true**, andernfalls `false`.

## Technische Besonderheiten
- **Adapterbasierte Kommunikation**: Alle Ein- und Ausgänge erfolgen über unidirektionale Adapter (Typen `AUI` und `AX`). Dies ermöglicht eine lose Kopplung und Wiederverwendung in verschiedenen Umgebungen.
- **Asynchrone Auslösung**: Da beide Ereigniseingänge auf den gleichen `REQ` des internen `F_LT` führen, kann der Vergleich durch ein Ereignis an **einem** der beiden Eingänge gestartet werden. Es ist nicht erforderlich, dass beide Ereignisse gleichzeitig eintreffen.
- **Typkompatibilität**: Der Baustein arbeitet mit beliebigen `ANY_BIT`-Datentypen (z. B. `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD`), sofern die angeschlossenen Adapter dies unterstützen.
- **Keine Zustandsspeicherung**: Der FB ist rein kombinatorisch; er speichert keine historischen Werte.

## Zustandsübersicht

Da der `AUI_LT` keine explizite Zustandsmaschine besitzt, existiert lediglich ein **impliziter Zustand**:

| Zustand | Beschreibung |
|---------|--------------|
| **Bereit** | Wartet auf ein Ereignis an IN1.E1 oder IN2.E1. Nach Auslösung wird der Vergleich durchgeführt und das Ergebnis über OUT ausgegeben. Der FB kehrt sofort in den Bereit-Zustand zurück. |

## Anwendungsszenarien
- **Grenzwertüberwachung**: Prüfen, ob ein Messwert unter einem Schwellwert liegt, z. B. `Temperatur < Grenzwert`.
- **Steuerungslogik**: Bedingte Aktivierung von Ausgängen, z. B. Ventil öffnen, wenn `Druck < Sollwert`.
- **Interlock-Bedingungen**: Sicherheitsabfragen, bei denen ein Betrieb nur erlaubt ist, wenn eine Größe kleiner als eine andere ist.
- **Vergleichsketten**: Kombination mit anderen Vergleichsbausteinen (z. B. `AUI_EQ`, `AUI_GT`) zur Realisierung komplexer logischer Bedingungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein    | Funktion              | Schnittstelle | Besonderheit |
|-------------|-----------------------|---------------|--------------|
| **AUI_LT**  | Kleiner als (`<`)     | Adapter (AUI, AX) | Asynchron, zwei separate Ereigniseingänge |
| **F_LT**    | Kleiner als (`<`)     | Standard-Ports (REQ/CNF, ANY_BIT) | Direkte Ereignis-/Datenports, kein Adapter |
| **AUI_EQ**  | Gleich (`=`)          | Adapter (AUI, AX) | Gleiche Struktur, anderer Vergleichsoperator |
| **AUI_GT**  | Größer als (`>`) | Adapter (AUI, AX) | Same structure, different comparison operator |

The `AUI_LT` offers particularly flexible integration into IEC 61131-3 compliant systems via its adapter interfaces, while the internal `F_LT` provides the standardized comparison logic.

## Conclusion

The `AUI_LT` is a compact and reliable function block for less-than comparisons in adapter-based automation environments. Its asynchronous event processing and loose coupling via adapters make it ideal for modular control applications where simple conditions need to be evaluated decentrally and in a resource-efficient manner.
