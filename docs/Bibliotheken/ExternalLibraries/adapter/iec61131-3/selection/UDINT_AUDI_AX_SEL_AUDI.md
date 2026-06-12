# UDINT_AUDI_AX_SEL_AUDI


![UDINT_AUDI_AX_SEL_AUDI](./UDINT_AUDI_AX_SEL_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `UDINT_AUDI_AX_SEL_AUDI` realisiert eine binäre Auswahl zwischen zwei Eingangsgrößen. Der ausgewählte Wert wird über einen Adapter als Ausgang bereitgestellt. Die Auswahl wird durch einen separaten Selektor-Größe gesteuert. Der Baustein dient zur flexiblen Umschaltung von Signalquellen in automatisierungstechnischen Anwendungen und folgt dem IEC 61499-Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| EI0 | Event | Set IN0 – triggert die Verarbeitung des Dateneingangs IN0 |

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignisausgänge am Interface. Das Ausgangsereignis wird über den Adapter `OUT` bereitgestellt (E1). Ereignisauslösung erfolgt nach erfolgreicher Selektion.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN0 | UDINT | Selektierbare Eingangsvariable (erste Quelle) |

### **Daten-Ausgänge**

Der FB besitzt keine direkten Datenausgänge am Interface. Der ausgewählte Datenwert wird über den Adapter `OUT` (D1) ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Kommentar |
|------|----------|-----|-----------|
| OUT | Plug (Ausgang) | `adapter::types::unidirectional::AUDI` | Ausgewählter Ausgang (Ereignis E1, Daten D1) |
| IN1 | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Selektierbare Eingangsvariable (zweite Quelle) |
| G | Socket (Eingang) | `adapter::types::unidirectional::AX` | Selektor (steuert die Auswahl) |

## Funktionsweise

Der FB führt eine binäre Selektion zwischen zwei Werten durch:  
- **IN0** (direkter UDINT-Dateneingang)  
- **IN1** (Wert aus dem Adapter, z. B. ein analoger oder digitaler Signalwert)  

Die Auswahl wird durch den Wert des **Selektors G** (vom Typ AX, typischerweise boolesch) gesteuert.  

Ein Ereignis an **EI0** startet die Verarbeitung mit dem Wert von **IN0**.  
Ereignisse an den Adaptern **IN1.E1** oder **G.E1** lösen ebenfalls eine Selektion aus (alle Ereignisse werden auf den internen Funktionsbaustein `F_SEL` geführt).  

Der interne `F_SEL` entspricht dem IEC 61131-3 SELECT-Operator:  
- Wenn G = FALSE → Ausgabe = IN0  
- Wenn G = TRUE → Ausgabe = IN1  

Nach der Selektion wird ein Ereignis am Ausgangsadapter **OUT.E1** ausgegeben und der ausgewählte Datenwert unter **OUT.D1** bereitgestellt.

## Technische Besonderheiten

- **Adapter-basierte Schnittstellen**: Ein- und Ausgänge sind als IEC 61499-Adapter realisiert, was eine modulare und wiederverwendbare Kapselung ermöglicht.  
- **Interner IEC 61131-3 Baustein**: Die eigentliche Selektionslogik wird durch den vordefinierten Baustein `F_SEL` abgebildet, der eine deterministische und normgerechte Auswahl garantiert.  
- **Ereignissynchronisation**: Alle eingehenden Ereignisse (EI0, IN1.E1, G.E1) führen zur selben Verarbeitung, sodass der Baustein auf verschiedene Triggerquellen reagieren kann.  
- **Typensicherheit**: Die Adapter- und Datentypen sind strikt definiert (UDINT für Daten, AX für Selektorsignal), was Fehler zur Entwurfszeit minimiert.

## Zustandsübersicht

Der Baustein verfügt über keinen expliziten Zustandsautomaten. Er arbeitet rein ereignisgesteuert: Bei jedem gültigen Ereignis wird die Selektion sofort neu berechnet und das Ausgangsereignis ausgelöst. Es gibt keine internen Speicherzustände außerhalb der transienten Verarbeitung.

## Anwendungsszenarien

- **Sollwertumschaltung**: Auswahl zwischen einem Festwert (IN0) und einem variablen Sollwert von einem übergeordneten System (IN1).  
- **Signalpfadumschaltung**: In der Prozessautomatisierung kann zwischen einem lokalen Sensor (IN0) und einem externen Messwert (IN1) umgeschaltet werden.  
- **Betriebsartwahl**: Steuerung der Ausgangsgröße in Abhängigkeit eines Betriebsartenschalters (G).  
- **Redundanzumschaltung**: Bei Ausfall eines Signals (IN1) wird automatisch auf den Ersatzwert (IN0) zurückgegriffen (durch entsprechende Ansteuerung von G).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Merkmal |
|----------|---------|
| **SEL (IEC 61131-3)** | Reine Funktionsbaustein- oder ST-Implementierung ohne Adapter; direkte Daten- und Ereignisports. |
| **UDINT_AUDI_AX_SEL_AUDI** | Erweiterte Variante mit Adapter-Schnittstellen, die eine lose Kopplung und Wiederverwendbarkeit in komplexen Netzwerken erleichtert. |
| **MUX (Multiplexer)** | Mehrkanalige Auswahl (oft >2 Eingänge) – dieser Baustein beschränkt sich auf zwei Quellen. |

## Fazit

Der FB `UDINT_AUDI_AX_SEL_AUDI` bietet eine zuverlässige und normgerechte binäre Auswahl für Automatisierungsanwendungen. Durch die Verwendung von IEC 61499-Adaptern und der Integration des standardisierten `F_SEL`-Bausteins ist er flexibel einsetzbar, leicht verständlich und nahtlos in bestehende 4diac-Projekte integrierbar. Seine klare Schnittstellenstruktur und ereignisgesteuerte Verarbeitung machen ihn zu einem grundlegenden Werkzeug für die Signalumschaltung in verteilten Systemen.