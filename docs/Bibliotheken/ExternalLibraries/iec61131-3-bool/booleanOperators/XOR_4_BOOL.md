# XOR_4_BOOL

```{index} single: XOR_4_BOOL
```

<img width="1383" height="304" alt="image" src="https://github.com/user-attachments/assets/50f4bab5-ea69-4673-9279-dcd715e0bef0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_4_BOOL` ist ein Standardbaustein zur Berechnung der logischen Exklusiv-ODER-Verknüpfung (XOR) für bis zu vier boolesche Eingangswerte. Er folgt dem IEC 61131-3 Standard und ist als generischer Baustein implementiert, der in Steuerungsanwendungen zur kombinatorischen Logikverarbeitung eingesetzt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Berechnung der XOR-Verknüpfung aus. Es ist mit allen vier Dateneingängen (`IN1` bis `IN4`) verknüpft.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis am Datenausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1** (BOOL): XOR-Eingang 1.
*   **IN2** (BOOL): XOR-Eingang 2.
*   **IN3** (BOOL): XOR-Eingang 3.
*   **IN4** (BOOL): XOR-Eingang 4.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der XOR-Verknüpfung aller aktiven Eingänge.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Eintreffen des Ereignisses `REQ` liest der Baustein die Werte aller vier booleschen Eingänge (`IN1`, `IN2`, `IN3`, `IN4`). Anschließend berechnet er das logische Exklusiv-ODER über diese Werte. Das Ergebnis `OUT` ist genau dann `TRUE` (1), wenn eine ungerade Anzahl der Eingänge den Wert `TRUE` aufweist. Ist die Anzahl der `TRUE`-Eingänge gerade (0, 2 oder 4), ist das Ergebnis `FALSE` (0). Nach der Berechnung wird das Bestätigungsereignis `CNF` zusammen mit dem Ergebniswert ausgegeben.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist mit dem Attribut `eclipse4diac::core::GenericClassName` als `'GEN_XOR'` gekennzeichnet. Dies ermöglicht eine flexible Instanziierung und Wiederverwendung innerhalb der 4diac-IDE.
*   **Ereignisgesteuerte Ausführung:** Die Funktionalität ist streng ereignisgesteuert. Eine Berechnung findet nur bei einem eingehenden `REQ`-Ereignis statt.
*   **Vier Eingänge:** Im Gegensatz zu einem einfachen 2-Eingang-XOR bietet dieser Baustein die direkte Verarbeitung von bis zu vier Signalen ohne zusätzliche Verschachtelung.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (speicherfrei, kombinatorisch). Sein Verhalten ist bei jedem Aufruf ausschließlich von den aktuellen Werten an den Dateneingängen abhängig.

## Anwendungsszenarien
*   **Paritätsprüfung:** Erkennung, ob eine ungerade Anzahl von Bedingungen (z.B. Fehlermeldungen, Grenzwertüberschreitungen) in einer Gruppe von vier Signalen aktiv ist.
*   **Steuerungslogik:** Implementierung von Sicherheitsschaltungen, bei denen genau eine von mehreren möglichen Eingangskombinationen eine Aktion auslösen darf.
*   **Verschachtelte Logikvereinfachung:** Ersetzung mehrerer hintereinandergeschalteter 2-Eingang-XOR-Bausteine durch einen einzigen `XOR_4_BOOL`-Block für bessere Übersichtlichkeit im Funktionsplan (FBD).

## Vergleich mit ähnlichen Bausteinen
*   **Standard XOR (2 Eingänge):** Ein klassischer XOR-Baustein mit nur zwei Eingängen. Der `XOR_4_BOOL` konsolidiert die Funktion mehrerer solcher Blöcke. Siehe: [XOR_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_4.md)
*   **OR_4_BOOL / AND_4_BOOL:** Diese Blöcke berechnen die logische ODER- bzw. UND-Verknüpfung über vier Eingänge. Die XOR-Verknüpfung unterscheidet sich fundamental, da sie den Fall, dass alle Eingänge `TRUE` sind, als `FALSE` bewertet.
*   **Parity-Check Blöcke:** Spezialisierte Blöcke zur Paritätsberechnung existieren oft für Datenworte (BYTE, WORD). `XOR_4_BOOL` bietet diese Funktion für einzelne Bits/Bool-Werte.

## Fazit
Der `XOR_4_BOOL` ist ein nützlicher und effizienter Standardbaustein für die Implementierung von Exklusiv-ODER-Logik mit bis zu vier Eingängen in 4diac-basierten Steuerungsapplikationen. Seine ereignisgesteuerte, zustandslose Architektur und die direkte Unterstützung mehrerer Eingänge machen ihn zu einer praktischen Wahl für Paritätschecks und spezielle kombinatorische Steuerungsaufgaben.