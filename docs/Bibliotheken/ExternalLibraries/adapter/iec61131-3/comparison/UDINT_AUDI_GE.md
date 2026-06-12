# UDINT_AUDI_GE


![UDINT_AUDI_GE](./UDINT_AUDI_GE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **UDINT_AUDI_GE** realisiert einen „greater or equal“-Vergleich (>=) für zwei Eingangswerte. Er entspricht der IEC-61131-3-Klassifikation für Standardvergleichsfunktionen. Das Ergebnis wird über einen gerichteten Adapter (Plugs/Sockets) ausgegeben, sodass der Baustein flexibel in typisierte Adapterstrukturen eingebunden werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Service Request – löst den Vergleich aus |

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge vorhanden. Das Ereignissignal wird über den **OUT**-Adapter (siehe Adapter) nach außen transportiert.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN1 | ANY_ELEMENTARY | Erster Vergleichswert |

### **Daten-Ausgänge**

Keine direkten Datenausgänge vorhanden. Der Ergebniswert wird über den **OUT**-Adapter (siehe Adapter) bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug | OUT | adapter::types::unidirectional::AX | Liefert das Vergleichsergebnis (true, wenn IN1 >= IN2) als Ereignis und Datenwert |
| Socket | IN2 | adapter::types::unidirectional::AUDI | Empfängt den zweiten Vergleichswert (IN2) als Ereignis und Datenwert |

## Funktionsweise

Der Baustein führt einen Vergleich der beiden Eingangswerte auf „größer oder gleich“ durch. Die interne Implementierung nutzt den Baustein **F_GE** (aus der Bibliothek `iec61131::comparison`). Der Ablauf:

1. Ein Ereignis an **REQ** oder ein eingehendes Ereignis vom **IN2**-Adapter triggert den Vergleich.
2. Der Datenwert **IN1** und der über den **IN2**-Adapter bereitgestellte Wert werden an **F_GE** übergeben.
3. Das Ergebnis (TRUE/FALSE) wird über den **OUT**-Adapter als Ereignis und als Datenwert ausgegeben.

Da der zweite Eingang über einen Adapter (Socket) realisiert ist, kann der Quellwert dynamisch von einem anderen Baustein oder einer Schnittstelle bereitgestellt werden.

## Technische Besonderheiten

- **Verwendung von unidirektionalen Adaptern:** Der Baustein ist nicht auf feste Eingänge angewiesen – der zweite Operand wird über einen Socket (IN2) empfangen. Der Ausgang erfolgt über einen Plug (OUT), sodass der Baustein in Adapter-basierte Architekturen integriert werden kann.
- **Flexible Datentypen:** IN1 ist als *ANY_ELEMENTARY* deklariert, was eine hohe Wiederverwendbarkeit für verschiedene numerische oder elementare Datentypen erlaubt.
- **Interne Kapselung:** Die Vergleichslogik ist als Unterbaustein (F_GE) realisiert, was Wartbarkeit und Wiederverwendung fördert.
- **Zwei Triggerquellen:** Das Ereignis REQ und das vom IN2-Adapter kommende Ereignis können den Vergleich auslösen. Dies ermöglicht eine asynchrone Datenbereitstellung.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Seine Funktionalität ist rein ereignisgesteuert: Bei jedem eingehenden Ereignis (REQ oder IN2.E1) wird der Vergleich neu ausgeführt und das Ergebnis über OUT ausgegeben.

## Anwendungsszenarien

- **Grenzwertüberwachung:** Vergleich von Messwerten aus verschiedenen Quellen (z. B. Sensoren, Datenbanken) gegen einen Schwellwert.
- **Adapterbasierte Datenflüsse:** Einbindung in eine Komponentenarchitektur, bei der Daten über standardisierte Adapter ausgetauscht werden (z. B. in der Automatisierungstechnik oder im IoT-Bereich).
- **Parametrierbare Vergleichsfunktion:** Dank des ANY_ELEMENTARY-Typs kann der Baustein für Ganzzahlen, Gleitkommazahlen oder andere elementare Typen genutzt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|--------------|
| UDINT_AUDI_GE | Größer oder gleich (>=) mit Adapter-basiertem zweiten Eingang |
| UDINT_GT (Greater Than) | Nur größer (>), ähnliche Adapterstruktur |
| UDINT_EQ (Equal) | Gleichheit (==) |
| Standard-F_GE | Ohne Adapter – beide Eingänge als direkte Variablen |

Der wesentliche Unterschied ist der Einsatz von Adaptern, was eine losere Kopplung und eine einfachere Einbindung in bestehende Adapter-Ökosysteme ermöglicht.

## Fazit

**UDINT_AUDI_GE** ist ein flexibler Vergleichsbaustein für „größer oder gleich“, der durch die Verwendung von unidirektionalen Adaptern besonders in modularen, adapterbasierten Architekturen (z. B. Eclipse 4diac) glänzt. Seine einfache Ereignissteuerung und die Unterstützung elementarer Datentypen machen ihn zu einem universellen Werkzeug für zahlreiche Vergleichsaufgaben in der Automatisierungstechnik.