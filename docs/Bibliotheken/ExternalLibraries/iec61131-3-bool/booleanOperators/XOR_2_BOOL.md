# XOR_2_BOOL

```{index} single: XOR_2_BOOL
```

<img width="1186" height="216" alt="image" src="https://github.com/user-attachments/assets/7c34009d-7063-4900-b45e-5b35629a05c0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_2_BOOL` ist ein Standardbaustein zur Berechnung der logischen Exklusiv-ODER-Verknüpfung (XOR) zweier boolescher Eingangssignale. Er gehört zur Kategorie der bitweisen Operatoren und ist als generischer Funktionsblock implementiert, der in Steuerungsanwendungen nach IEC 61131-3 eingesetzt wird. Der Baustein wartet auf eine Ausführungsanforderung, berechnet das Ergebnis und gibt dieses zusammen mit einer Bestätigung zurück.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Normale Ausführungsanforderung. Löst die Berechnung der XOR-Verknüpfung aus. Die mit diesem Ereignis verknüpften Daten (`IN1`, `IN2`) werden bei der Verarbeitung gelesen.

### **Ereignis-Ausgänge**
*   **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach der Berechnung generiert und signalisiert die Verfügbarkeit des Ergebnisses. Es ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
*   **IN1**: Boolescher Eingang 1 für die XOR-Operation.
*   **IN2**: Boolescher Eingang 2 für die XOR-Operation.

### **Daten-Ausgänge**
*   **OUT**: Boolesches Ergebnis der XOR-Verknüpfung von `IN1` und `IN2`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Der `XOR_2_BOOL`-Block arbeitet ereignisgesteuert. Bei Eintreffen des Ereignisses `REQ` werden die aktuellen Werte an den Daten-Eingängen `IN1` und `IN2` gelesen. Anschließend wird die logische XOR-Operation (`OUT = (IN1 AND NOT IN2) OR (NOT IN1 AND IN2)`) durchgeführt. Das berechnete Ergebnis wird am Datenausgang `OUT` ausgegeben und gleichzeitig wird das Bestätigungsereignis `CNF` aktiviert, um den Abschluss der Operation an nachfolgende Blöcke zu signalisieren.

Die Wahrheitstabelle der Operation ist:
| IN1 | IN2 | OUT |
|-----|-----|-----|
| 0   | 0   | 0   |
| 0   | 1   | 1   |
| 1   | 0   | 1   |
| 1   | 1   | 0   |

## Technische Besonderheiten
*   **Generischer Baustein**: Der Block ist mit dem generischen Klassennamen `'GEN_XOR'` gekennzeichnet, was seine Wiederverwendbarkeit und mögliche Integration in übergeordnete Strukturen erleichtert.
*   **Ereignisgesteuerte Ausführung**: Die Funktionalität ist strikt an die Eingangsereignisse gekoppelt, was eine deterministische und energieeffiziente Abarbeitung in Echtzeitsystemen ermöglicht.
*   **Einfache Schnittstelle**: Der Block besitzt eine minimale und intuitive Schnittstelle, die der klassischen, in der Digitaltechnik üblichen XOR-Funktion entspricht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist kombinatorisch und ausschließlich von den aktuellen Eingangswerten bei Eintreffen des `REQ`-Ereignisses abhängig. Der Block verharrt nach der Ausgabe von `CNF` in einem wartenden Zustand, bis das nächste `REQ`-Ereignis eintrifft.

## Anwendungsszenarien
*   **Vergleich und Änderungserkennung**: Erkennung, wenn sich genau einer von zwei Zuständen (z.B. zwei Endschalter) geändert hat.
*   **Paritätsprüfung**: Einfache Prüfung auf eine ungerade Anzahl von `TRUE`-Signalen bei zwei Eingängen.
*   **Steuerungslogik**: Implementierung von speziellen Verzweigungen in Ablaufsteuerungen, bei denen eine Entscheidung getroffen werden muss, wenn die Eingänge unterschiedlich sind.
*   **Sicherheitskritische Schaltungen**: Erzeugung von Signalen, die nur aktiv sind, wenn sich zwei überwachte Größen widersprechen (z.B. in Not-Halt-Schaltungen).

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logischen Grundfunktionsblöcken wie `AND_2_BOOL` oder `OR_2_BOOL` ist `XOR_2_BOOL` der einzige, der ein `TRUE`-Ergebnis liefert, wenn die Eingänge *unterschiedlich* sind. Blöcke wie `NOT` invertieren nur einen einzelnen Eingang. Der `XOR_2_BOOL` kann als Spezialfall eines Ungleichheitsvergleichs (`NE_BOOL`) für zwei boolesche Werte betrachtet werden. Siehe: [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md)

## Fazit
Der `XOR_2_BOOL` ist ein grundlegender, zuverlässiger und einfach zu verwendender Baustein für die logische Verknüpfung in IEC 61131-3-basierten Steuerungsapplikationen. Seine ereignisgesteuerte, zustandslose Architektur macht ihn besonders geeignet für die Integration in komplexe, deterministische Steuerungsnetzwerke. Durch seine klare Funktionsweise und minimale Schnittstelle ist er ein unverzichtbares Werkzeug für jeden Steuerungsentwickler.