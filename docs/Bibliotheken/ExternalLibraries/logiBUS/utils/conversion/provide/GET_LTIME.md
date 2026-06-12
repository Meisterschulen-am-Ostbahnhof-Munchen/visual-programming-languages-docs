# GET_LTIME


![GET_LTIME](./GET_LTIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **GET_LTIME** dient dazu, den aktuellen Wert einer LTIME-Variablen auszulesen und als gepufferten Ausgangswert bereitzustellen. Er greift über eine InOut-Schnittstelle auf die Quelle zu und stellt den gelesenen Wert am Ausgang zur Verfügung, sobald ein Ereignis eintrifft. Dies ermöglicht ein kontrolliertes, einmaliges Auslesen einer Zeitvariablen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Normaler Ausführungsauftrag. Verbunden mit dem Eingangswert IN. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung der Ausführung. Verbunden mit den Ausgängen OUT und IN. |

### **Daten-Eingänge**
Der Baustein besitzt keine klassischen Dateneingänge. Der Zugriff auf den Quellwert erfolgt ausschließlich über die InOut-Variable.

### **Daten-Ausgänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| OUT  | LTIME    | Gepufferter Ausgabewert (Initialwert LT#0s). |

### **Adapter**
Keine.

## Funktionsweise
Der Funktionsbaustein implementiert eine einfache, ereignisgesteuerte Kopierlogik:

1. Ein eingehendes Ereignis **REQ** löst die Ausführung des internen Algorithmus aus.
2. Der Algorithmus weist dem Ausgang **OUT** den aktuellen Wert der InOut-Variablen **IN** zu (`OUT := IN;`).
3. Nach erfolgreicher Zuweisung wird das Ausgangsereignis **CNF** gesendet, um der aufrufenden Instanz die Fertigstellung zu signalisieren.

Somit wird der Wert der externen LTIME-Variablen nur zu dem Zeitpunkt gelesen, an dem das REQ-Ereignis eintrifft, und bis zum nächsten Lesen im Ausgang zwischengespeichert.

## Technische Besonderheiten
- **InOut-Variable**: Der Zugriff auf die Quelle erfolgt über eine InOut-Schnittstelle, die eine direkte Referenz auf eine externe Variable darstellt. Änderungen an der externen Variable zwischen zwei REQ-Aufrufen werden erst beim nächsten Lesevorgang übernommen.
- **Pufferung**: Der gelesene Wert bleibt am Ausgang OUT erhalten, bis ein erneutes REQ-Ereignis eingeht. Dies schützt vor asynchronen Änderungen der Quelle während der Verarbeitung.
- **Rücklesen des Eingangs**: Das Ereignis **CNF** ist nicht nur mit OUT, sondern auch mit IN verbunden. Dies kann in bestimmten Laufzeitumgebungen genutzt werden, um die Weiterleitung des InOut-Wertes zu steuern, hat jedoch im Standardverhalten keine zusätzliche funktionale Bedeutung.

## Zustandsübersicht
Der Baustein ist als SimpleFB realisiert und besitzt genau einen internen Zustand:

| Zustand | Aktion | Ausgangsereignis |
|---------|--------|------------------|
| REQ     | Algorithmus REQ (OUT := IN) | CNF |

Nach dem Empfang von **REQ** wird der Zustand einmalig durchlaufen und die Ausgabe erzeugt. Es gibt keine weiteren Zustände oder Verzweigungen.

## Anwendungsszenarien
- **Zeitstempel-Erfassung**: Einmaliges Einfrieren eines aktuellen Systemzeitwerts (LTIME) zu einem bestimmten Ereignis, z. B. bei einem Alarmsignal.
- **Synchronisation von Zeitmessungen**: Auslesen eines gemeinsamen Zeitzählers in einer industriellen Steuerung, um konsistente Zeitdaten an verschiedene nachfolgende Bausteine weiterzugeben.
- **Pufferung von Zeitwerten** in datengetriebenen Architekturen, bei denen eine LTIME-Variable mehrfach verwendet wird, aber exakt zum selben Zeitpunkt gelesen werden soll.

## Vergleich mit ähnlichen Bausteinen
- **GET_VALUE (für andere Datentypen)**: Funktionsweise analog, jedoch für skalare Datentypen wie INT, REAL etc. GET_LTIME ist auf den Datentyp LTIME spezialisiert.
- **Latch-Funktionsbausteine**: Während Latch-Bausteine einen Wert bei einem Ereignis speichern und halten, erzeugt GET_LTIME zusätzlich ein Bestätigungsereignis und liest aus einer InOut-Variablen statt aus einem normalen Dateneingang.
- **MOVE-Baustein**: Ein MOVE kopiert ebenfalls einen Wert von einem Eingang auf einen Ausgang, jedoch ohne Ereignissteuerung und ohne InOut-Unterstützung. GET_LTIME bietet eine ereignisgesteuerte, gepufferte Variante.

## Fazit
Der Baustein **GET_LTIME** ist eine einfache, aber effektive Komponente zum kontrollierten Auslesen einer LTIME-Variablen über eine InOut-Schnittstelle. Seine ereignisgesteuerte Arbeitsweise und die Pufferung des Ausgangswerts machen ihn besonders geeignet für zeitkritische Anwendungen, bei denen ein konsistenter Zeitwert zu einem definierten Zeitpunkt benötigt wird. Die klare Schnittstelle und die einfache Zustandslogik erleichtern die Integration in größere Steuerungsanwendungen.