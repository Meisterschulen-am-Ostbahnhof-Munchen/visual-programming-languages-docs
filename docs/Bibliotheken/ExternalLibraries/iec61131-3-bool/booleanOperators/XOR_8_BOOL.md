# XOR_8_BOOL

```{index} single: XOR_8_BOOL
```

<img width="1381" height="423" alt="image" src="https://github.com/user-attachments/assets/6d43c16c-0360-452c-bd8f-8caac2a5b590" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_8_BOOL` ist ein generischer Baustein zur Berechnung der logischen Exklusiv-ODER-Verknüpfung (XOR) über bis zu acht boolesche Eingangswerte. Er folgt dem IEC 61131-3 Standard und ist für den Einsatz in der 4diac-IDE konzipiert. Der Block führt seine Operation ereignisgesteuert aus und liefert das Ergebnis über einen einzelnen booleschen Ausgang.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Berechnung aus. Es ist mit allen acht Dateneingängen (`IN1` bis `IN8`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
*   **IN1** (BOOL): XOR-Eingang 1.
*   **IN2** (BOOL): XOR-Eingang 2.
*   **IN3** (BOOL): XOR-Eingang 3.
*   **IN4** (BOOL): XOR-Eingang 4.
*   **IN5** (BOOL): XOR-Eingang 5.
*   **IN6** (BOOL): XOR-Eingang 6.
*   **IN7** (BOOL): XOR-Eingang 7.
*   **IN8** (BOOL): XOR-Eingang 8.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Das Ergebnis der XOR-Verknüpfung aller aktiven Eingänge.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Eintreffen des Ereignisses `REQ` liest der Funktionsblock die Werte aller acht booleschen Eingänge (`IN1` bis `IN8`). Anschließend berechnet er das logische Exklusiv-ODER über alle diese Eingangswerte. Das Ergebnis dieser Berechnung wird am Datenausgang `OUT` ausgegeben und gleichzeitig wird das Bestätigungsereignis `CNF` gesetzt, um den Abschluss des Vorgangs zu signalisieren.

Die logische Funktion lässt sich wie folgt beschreiben:
`OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5 XOR IN6 XOR IN7 XOR IN8`

Ein XOR (Exklusiv-ODER) liefert genau dann `TRUE` (1) als Ergebnis, wenn eine ungerade Anzahl der verknüpften Eingänge `TRUE` (1) ist. Ist die Anzahl der wahren Eingänge gerade, ist das Ergebnis `FALSE` (0).

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein (`GEN_XOR`) gekennzeichnet, was seine Wiederverwendbarkeit und mögliche Parametrierung für andere Datentypen andeutet. In dieser konkreten Instanz ist er jedoch auf den Datentyp `BOOL` festgelegt.
*   **Ereignisgesteuerte Ausführung:** Die Operation wird nur bei einem eingehenden `REQ`-Ereignis durchgeführt, was eine effiziente und deterministische Ablaufsteuerung ermöglicht.
*   **Feste Eingangsanzahl:** Der Block bietet genau acht Eingänge. Nicht benötigte Eingänge sollten auf einen definierten logischen Wert (z.B. `FALSE`) gesetzt werden.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und ereignisgesteuert:
1.  **Ruhezustand:** Wartet auf das Eintreffen des `REQ`-Ereignisses.
2.  **Berechnungszustand:** Bei `REQ` werden alle Eingänge gelesen und die XOR-Operation durchgeführt.
3.  **Ausgabezustand:** Das Ergebnis wird an `OUT` ausgegeben und das `CNF`-Ereignis wird generiert. Anschließend kehrt der Block in den Ruhezustand zurück.

## Anwendungsszenarien
*   **Paritätsprüfung:** Erkennung, ob eine ungerade Anzahl von Signalen (z.B. Fehlermeldungen, Grenzwertüberschreitungen) in einer Gruppe aktiv ist.
*   **Umschaltlogik:** Steuerung, bei der eine Aktion nur dann ausgeführt werden soll, wenn genau eines von mehreren möglichen Steuersignalen aktiv ist (z.B. Wahl zwischen manuellem und automatischem Modus).
*   **Verschlüsselungs- und Codierungsgrundfunktionen:** Als Basisbaustein für einfache kryptografische Operationen oder Fehlererkennungscodes.
*   **Vergleich von zwei oder mehr Zuständen:** Feststellung, ob sich mindestens ein Signal in einer Gruppe von seinem Sollzustand unterscheidet.

## Vergleich mit ähnlichen Bausteinen
*   **`OR_8_BOOL` / `AND_8_BOOL`:** Diese Blöcke berechnen die logische ODER- bzw. UND-Verknüpfung. Im Gegensatz zum XOR liefert ODER `TRUE`, wenn *mindestens* ein Eingang wahr ist, und UND liefert `TRUE` nur, wenn *alle* Eingänge wahr sind. XOR ist spezifischer und reagiert auf die *Parität* (gerade/ungerade) der wahren Eingänge.
*   **`XOR` (mit 2 Eingängen):** Ein Standard-XOR-Block mit nur zwei Eingängen. `XOR_8_BOOL` erweitert diese Funktionalität auf bis zu acht Eingänge, ohne dass mehrere Blöcke verkettet werden müssen. Siehe: [XOR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_8.md)
*   **Kombinatorische Logik in SFC/ST:** Die Funktion könnte auch in Structured Text (ST) direkt programmiert werden (z.B. `OUT := IN1 XOR IN2 XOR ...;`). Der Vorteil des FBs liegt in der standardisierten, wiederverwendbaren und grafisch darstellbaren Schnittstelle innerhalb von FBD-Netzwerken.

## Fazit
Der `XOR_8_BOOL` ist ein spezialisierter, zuverlässiger und einfach zu verwendender Funktionsblock für logische XOR-Operationen mit bis zu acht Eingängen. Seine ereignisgesteuerte Architektur macht ihn ideal für die Integration in steuerungstypische Ablaufstrukturen der 4diac-IDE. Er eignet sich besonders für Anwendungen, bei denen die Parität von Signalgruppen von Bedeutung ist, und bietet eine klar definierte Alternative zu den grundlegenden ODER- und UND-Verknüpfungen.
