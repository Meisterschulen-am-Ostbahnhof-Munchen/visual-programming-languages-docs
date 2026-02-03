# OR_5_BOOL

```{index} single: OR_5_BOOL
```

<img width="1370" height="337" alt="image" src="https://github.com/user-attachments/assets/d3d2531f-35f3-4013-86ae-fbe3da61ed57" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_5_BOOL` ist ein Standardbaustein zur Berechnung der logischen ODER-Verknüpfung. Er führt eine ODER-Operation über fünf separate boolesche Eingangssignale aus. Der Baustein gehört zur Kategorie der Standard-Booleschen Funktionen gemäß IEC 61131-3 und ist als generischer Baustein implementiert.

![OR_5_BOOL](OR_5_BOOL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Beim Eintreffen von `REQ` werden die Werte aller fünf Eingänge (`IN1` bis `IN5`) gelesen und die ODER-Operation berechnet.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis signalisiert den Abschluss der Berechnung. Es wird zusammen mit dem berechneten Ergebnis `OUT` ausgegeben.

### **Daten-Eingänge**
*   **IN1 (BOOL):** ODER-Eingang 1.
*   **IN2 (BOOL):** ODER-Eingang 2.
*   **IN3 (BOOL):** ODER-Eingang 3.
*   **IN4 (BOOL):** ODER-Eingang 4.
*   **IN5 (BOOL):** ODER-Eingang 5.

### **Daten-Ausgänge**
*   **OUT (BOOL):** Das Ergebnis der ODER-Verknüpfung aller fünf Eingänge. Der Ausgang ist `TRUE`, wenn mindestens einer der Eingänge `IN1` bis `IN5` den Wert `TRUE` hat.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und ereignisgesteuert:
1.  Das Eintreffen des Ereignisses `REQ` startet die Ausführung.
2.  Der Block liest die aktuellen Werte der fünf booleschen Eingänge `IN1` bis `IN5`.
3.  Es wird die logische ODER-Verknüpfung `OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5` berechnet.
4.  Das Ergebnis wird am Datenausgang `OUT` bereitgestellt und gleichzeitig wird das Bestätigungsereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation an nachfolgende Blöcke zu signalisieren.

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist mit dem Attribut `eclipse4diac::core::GenericClassName` als `'GEN_OR'` gekennzeichnet. Dies deutet darauf hin, dass er Teil einer Familie generischer ODER-Bausteine mit unterschiedlicher Anzahl an Eingängen ist.
*   **Package:** Der Baustein ist im Package `iec61131::bitwiseOperators` enthalten.
*   **Ereignisgesteuerte Ausführung:** Die Berechnung erfolgt nur bei Anforderung durch ein `REQ`-Ereignis, was eine energieeffiziente und deterministische Ablaufsteuerung ermöglicht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und hängt ausschließlich von den aktuellen Eingangswerten zum Zeitpunkt des `REQ`-Ereignisses ab. Der Block kehrt nach dem Auslösen von `CNF` in einen passiven Wartezustand zurück.

## Anwendungsszenarien
Typische Anwendungen sind in Steuerungslogik zu finden, wo eine Bedingung als erfüllt gilt, wenn eine von mehreren möglichen Teilbedingungen zutrifft:
*   Überwachung: Alarmauslösung, wenn mindestens eines von mehreren Überwachungssensoren einen Grenzwert überschreitet.
*   Freigabelogik: Start einer Maschine, wenn mindestens eine von mehreren Sicherheitseinrichtungen aktiviert ist.
*   Auswahl- oder Priorisierungslogik in verbundenen Steuerungssystemen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu diesem Baustein mit fünf festen Eingängen existieren in 4diac oft auch:
*   **OR_2_BOOL, OR_3_BOOL, etc.:** Gleiche Funktionalität, aber mit einer geringeren, festen Anzahl an Eingängen (z.B. 2, 3, 4). Siehe: [OR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_5.md)
*   **GEN_OR (Generisches ODER):** Ein übergeordneter, konfigurierbarer Baustein, der je nach Instanziierung eine variable Anzahl von Eingängen besitzen kann. `OR_5_BOOL` ist eine spezifische Instanziierung dieses Prinzips.
*   **AND_5_BOOL:** Führt eine logische UND-Verknüpfung über alle fünf Eingänge aus (Ergebnis ist nur `TRUE`, wenn *alle* Eingänge `TRUE` sind).

## Fazit
Der `OR_5_BOOL` ist ein einfacher, robuster und standardkonformer Funktionsblock zur Realisierung einer ODER-Verknüpfung mit fünf Eingängen. Seine ereignisgesteuerte Architektur integriert sich nahtlos in die Funktionsbaustein-Netzwerke von 4diac und eignet sich ideal für klare und übersichtliche Logikverknüpfungen in Automatisierungsanwendungen.