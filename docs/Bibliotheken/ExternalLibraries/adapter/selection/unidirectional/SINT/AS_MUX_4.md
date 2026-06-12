# AS_MUX_4


![AS_MUX_4](./AS_MUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_MUX_4** ist ein generischer Multiplexer für unidirektionale AS-Datenströme. Er ermöglicht die Auswahl eines von vier AS-Eingängen (IN1…IN4) und stellt den gewählten Datenstrom an den AS-Ausgang (OUT) bereit. Die Auswahl erfolgt über einen Index K, der beim Eintreffen des Ereignisses REQ ausgewertet wird. Der Baustein wird in der 4diac-IDE eingesetzt und ist als generischer FB mit dem Klassennamen `GEN_AS_MUX` hinterlegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

Der Eingang **REQ** löst die Multiplex-Operation aus. Bei jedem Ereignis wird der aktuelle Wert von **K** gelesen und der entsprechende AS-Eingang an den Ausgang durchgeschaltet.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben. Es bestätigt, dass die durch den Index **K** bestimmte Verbindung hergestellt ist.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index (0…3) |

Der Dateneingang **K** definiert den auszuwählenden Pfad. Gültige Werte sind 0 bis 3 für die Eingänge IN1 bis IN4.

### **Daten-Ausgänge**

Keine expliziten Datenausgänge, da der Ausgang als AS-Adapter (Plug) realisiert ist.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| OUT  | adapter::types::unidirectional::AS | Plug | AS-Ausgang: liefert den Datenstrom des ausgewählten Eingangs |
| IN1  | adapter::types::unidirectional::AS | Socket | AS-Eingang 1 (Index 0) |
| IN2  | adapter::types::unidirectional::AS | Socket | AS-Eingang 2 (Index 1) |
| IN3  | adapter::types::unidirectional::AS | Socket | AS-Eingang 3 (Index 2) |
| IN4  | adapter::types::unidirectional::AS | Socket | AS-Eingang 4 (Index 3) |

Die Adapter sind vom Typ `adapter::types::unidirectional::AS`. Der Plug **OUT** wird mit dem ausgewählten Socket verbunden; alle nicht ausgewählten Sockets bleiben inaktiv.

## Funktionsweise

Der Funktionsblock arbeitet ereignisgesteuert:

1. Ein Ereignis am Eingang **REQ** triggert die Verarbeitung.
2. Der aktuelle Wert des Dateneingangs **K** wird gelesen.
3. Abhängig von **K** (0, 1, 2 oder 3) wird der entsprechende AS-Eingang (**IN1**, **IN2**, **IN3** oder **IN4**) auf den AS-Ausgang **OUT** geschaltet.
4. Nach der Umschaltung wird das Bestätigungsereignis **CNF** ausgegeben.

Der Baustein besitzt keine interne Datenhaltung oder Zustandsmaschine; die Umschaltung erfolgt bei jedem REQ-Ereignis neu.

## Technische Besonderheiten

- **Generische Implementierung:** Der FB ist als generischer Baustein (`GEN_AS_MUX`) deklariert, was eine einfache Wiederverwendung und Anpassung in verschiedenen Projekten ermöglicht.
- **Adapterbasierte Kommunikation:** Der gesamte Datenfluss erfolgt über AS-Adapter, nicht über einzelne Datenports. Dies vereinfacht die Verbindung mit anderen AS-kompatiblen Bausteinen.
- **Eingeschränkter Indexbereich:** Der Index **K** muss im Wertebereich 0…3 liegen; Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten. Eine Plausibilitätsprüfung obliegt der Anwendung.
- **Kein interner Zustand:** Der FB hat keinen ECC (Execution Control Chart) – die Verarbeitung erfolgt direkt und ohne Verzögerung bei jedem REQ.

## Zustandsübersicht

Der Funktionsblock besitzt **keine explizite Zustandsmaschine**. Es gibt nur einen impliziten Zustand „Bereit“, in dem er auf ein REQ-Ereignis wartet. Nach Eintreffen von REQ wird die Umschaltung ausgeführt und sofort CNF gesendet. Ein Fehlerzustand ist nicht definiert.

## Anwendungsszenarien

- **Sensordatenauswahl:** Auswahl eines von vier analogen oder digitalen Sensorwerten, die über AS‑Adapter bereitgestellt werden.
- **Parametrierung:** Umschaltung zwischen verschiedenen Parametersätzen in einer Steuerungslogik.
- **Signalrouting:** Selektives Durchschalten von AS-Datenströmen in Abhängigkeit eines Steuerindex.
- **Test- und Simulationsumgebungen:** Gezielte Auswahl von Testsignalen für Prüfzwecke.

## Vergleich mit ähnlichen Bausteinen

- **AS_MUX_2:** Ein Multiplexer mit nur zwei Eingängen. Der vorliegende FB erweitert die Flexibilität auf vier Eingänge.
- **Standard-MUX-FBs:** Oft mit einzelnen Datenports (z. B. INT, BOOL) realisiert. Der hier gezeigte FB hingegen arbeitet ausschließlich mit AS-Adaptern, was eine konsistente Datenübertragung in AS-basierten Systemen ermöglicht.
- **Dekomposition in mehrere AS_MUX_2:** Prinzipiell möglich, aber weniger effizient und übersichtlich.

## Fazit

Der Funktionsblock **AS_MUX_4** bietet eine elegante und flexible Möglichkeit, aus vier AS-Datenquellen eine auszuwählen. Durch die adapterbasierte Schnittstelle fügt er sich nahtlos in die 4diac-IDE und in AS-Kommunikationsstrukturen ein. Seine einfache, ereignisgesteuerte Funktionsweise macht ihn zu einem Grundbaustein für Selektionsaufgaben in der Automatisierungstechnik. Die generische Auslegung erlaubt eine problemlose Integration in unterschiedlichste Projekte.