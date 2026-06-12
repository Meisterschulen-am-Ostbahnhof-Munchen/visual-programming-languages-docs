# AUDI_AX_SEL


![AUDI_AX_SEL](./AUDI_AX_SEL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_AX_SEL** realisiert eine binäre Auswahl (binary selection) zwischen zwei Datenwerten. Er nimmt zwei Eingabewerte entgegen, die jeweils über separate Ereignisse gesetzt werden, und gibt bei einem über einen Adapter gesteuerten Auswahlereignis den entsprechenden Wert aus. Der Baustein integriert einen standardisierten IEC-61131-3-Selektor (F_SEL) und erweitert ihn um ereignisgesteuerte Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `EI0` | Event | Setzt den Wert für `IN0` |
| `EI1` | Event | Setzt den Wert für `IN1` |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung der angefragten Auswahl (wird nach erfolgreicher Verarbeitung ausgegeben) |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `IN0` | UDINT | Erster auswählbarer Wert |
| `IN1` | UDINT | Zweiter auswählbarer Wert |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `OUT` | UDINT | Ausgewählter Wert (entspricht `IN0` oder `IN1`) |

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `G` | `AX` (unidirektional) | Steuert die Auswahl über ein Ereignis (`E1`) und ein Datum (`D1`) |

## Funktionsweise

Der Baustein ist intern aus dem Standard-Funktionsblock `F_SEL` (IEC 61131-3) aufgebaut.

1. **Wertübernahme**: Durch Eintreffen der Ereignisse `EI0` oder `EI1` werden die entsprechenden Datenwerte an den internen Selektor weitergeleitet. `EI0` setzt den Wert für `IN0`, `EI1` setzt den Wert für `IN1`.

2. **Auswahl**: Der Adapter `G` stellt eine Steuerschnittstelle dar. Wenn das Ereignis `G.E1` empfangen wird, wird der interne `F_SEL`-Baustein über seinen `REQ`-Eingang getriggert. Das Datum `G.D1` (Typ Bool – implizit durch den Adapter vorgegeben) bestimmt, welcher Eingang ausgewählt wird:
   - `G.D1 = FALSE` → `OUT = IN0`
   - `G.D1 = TRUE`  → `OUT = IN1`

3. **Ausgabe**: Nach erfolgter Auswahl wird der Ergebniswert auf dem Ausgang `OUT` ausgegeben und das Bestätigungsereignis `CNF` gesendet.

Der Adapter ermöglicht eine lose Kopplung der Steuerlogik; die eigentliche Auswahlentscheidung kann von einem anderen Baustein oder einer übergeordneten Komponente bereitgestellt werden.

## Technische Besonderheiten

- **Integration eines IEC-61131-3-Standardbausteins**: Intern wird `F_SEL` verwendet, sodass die Auswahl semantisch und zeitlich dem industriellen Standard entspricht.
- **Adapter-basierte Steuerung**: Die Auswahlentscheidung erfolgt nicht über einen direkten Bool-Eingang, sondern über einen unidirektionalen Adapter `AX`. Dies verbessert die Modularität und erlaubt den Austausch der Steuerlogik, ohne den Baustein zu verändern.
- **Ereignisgesteuerte Wertesetzung**: Jeder Eingangswert wird über ein eigenes Ereignis gesetzt – dies erlaubt asynchrone Aktualisierungen, bevor die finale Auswahl getriggert wird.

## Zustandsübersicht

Der Baustein besitzt eine implizite Zustandslogik, die sich auf das Verhalten des internen `F_SEL` stützt:

1. **Idle**: Kein Ereignis eingetroffen. Ausgang `OUT` bleibt auf dem letzten Wert.
2. **Setzen von IN0 / IN1**: Bei Eintreffen von `EI0` oder `EI1` werden die entsprechenden internen Kopien aktualisiert.
3. **Auswahl abwarten**: Nachdem die Werte gesetzt sind, wartet der Baustein auf das Ereignis `G.E1`.
4. **Auswahl durchführen**: Beim Eintreffen von `G.E1` wird `F_SEL` aktiviert. Anhand des Bool-Wertes von `G.D1` wird `OUT` auf den passenden Wert gesetzt.
5. **Bestätigung**: Nach Abschluss der Auswahl wird `CNF` erzeugt. Der Baustein kehrt in den Zustand „Idle“ zurück.

## Anwendungsszenarien

- **Agrartechnik**: Auswahl zwischen zwei Sensorwerten (z. B. Drehzahl-, Druck- oder Füllstandsmessungen) abhängig von einer Steuerentscheidung (z. B. Lastzustand).
- **Signalführung**: Umschalten zwischen redundanten Signalquellen in sicherheitskritischen Systemen.
- **Parametrierbare Durchschaltung**: In modularen Automatisierungssystemen kann der Adapter `G` mit einem übergeordneten Konfigurationsbaustein verbunden werden, der die Auswahl dynamisch vorgibt.

## Vergleich mit ähnlichen Bausteinen

- **Standard `SEL` (IEC 61131-3)**: Der nackte `SEL`-Baustein besitzt nur Bool- und Wert-Eingänge ohne Ereignissteuerung. `AUDI_AX_SEL` fügt eine ereignisgesteuerte Wertübernahme und eine Adapter-basierte Auswahlentscheidung hinzu, was die Integration in ereignisorientierte Steuerungen erleichtert.
- **„Bistabiler Schalter“ (Flipflop-basierte Auswahl)**: Im Gegensatz zu einem Flipflop arbeitet `AUDI_AX_SEL` rein kombinatorisch bei der Auswahl und speichert die Eingangswerte nicht über Ausführungsgrenzen hinweg. Die Auswahl erfolgt immer frisch beim Eintreffen von `G.E1`.
- **Weitere Adapter-basierte Selektoren**: Ähnliche Bausteine existieren in Bibliotheken für verteilte Automatisierung (z. B. 4diac LIB). `AUDI_AX_SEL` zeichnet sich durch den expliziten Einsatz des genormten `F_SEL` und die klare Trennung von Datenbereitstellung und Auswahl aus.

## Fazit

Der Funktionsblock `AUDI_AX_SEL` ist ein modularer, ereignisgesteuerter binärer Selektor, der speziell für den Einsatz in IEC-61499-basierten Automatisierungslösungen konzipiert wurde. Durch die Kombination von Ereignisschnittstellen und einem standardisierten IEC-61131-3-Selektor bietet er eine flexible, robuste und normenkonforme Lösung für Umschaltaufgaben in industriellen und agrotechnischen Umgebungen.