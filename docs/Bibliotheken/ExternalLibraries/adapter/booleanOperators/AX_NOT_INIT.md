# AX_NOT_INIT


![AX_NOT_INIT](./AX_NOT_INIT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_NOT_INIT** realisiert eine boolesche Negation (NOT-Funktion) auf Basis eines Adaptertyps. Im Gegensatz zu klassischen NOT-Bausteinen arbeitet er über eine standardisierte Adapterschnittstelle und ist speziell für die Verwendung in modularen Automatisierungssystemen konzipiert. Die Initialisierung erfolgt über den Ereigniseingang INIT, der die erste Berechnung auslöst.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ   | Kommentar               |
|-------|-------|-------------------------|
| INIT  | EInit | Initialisierungsanforderung |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                 |
|-------|-------|---------------------------|
| INITO | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**

Der Baustein besitzt keine direkten Dateneingänge. Die Eingangsdaten werden über den Adapter **IN** bezogen.

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Die Ausgangsdaten werden über den Adapter **OUT** bereitgestellt.

### **Adapter**

| Name | Typ                                              | Kommentar            | Richtung |
|------|--------------------------------------------------|----------------------|----------|
| IN   | adapter::types::unidirectional::AX               | Eingangswert         | Socket   |
| OUT  | adapter::types::unidirectional::AX               | Ausgangswert (negiert)| Plug     |

## Funktionsweise

Der Baustein führt eine bitweise Negation des über den **IN**-Adapter bereitgestellten Wertes durch und gibt das Ergebnis über den **OUT**-Adapter aus. Die Verarbeitung wird durch ein Ereignis am **IN.E1** (Ereignis aus dem IN-Adapter) oder durch das INIT-Ereignis gestartet. Interne Schritte:

1. Ein Ereignis an **INIT** oder **IN.E1** aktiviert den eingebetteten Funktionsblock **F_NOT_BOOL**.
2. **F_NOT_BOOL** holt den Wert von **IN.D1**, invertiert ihn und schreibt das Ergebnis nach **OUT.D1**.
3. Nach Abschluss wird ein Ereignis über **OUT.E1** (an den OUT-Adapter) sowie **INITO** ausgegeben.

Wird das INIT-Ereignis empfangen, so werden **INITO** und **OUT.E1** sofort ausgelöst – die erste Negation erfolgt ohne vorheriges Eingangsereignis.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**: Der Baustein verwendet ausschließlich unidirektionale Adapter vom Typ `AX`, wodurch die Daten- und Ereignisschnittstellen modular gekapselt werden. Dies erleichtert den Austausch zwischen Komponenten mit standardisierten Protokollen.
- **Initialisierungsverhalten**: Der INIT-Eingang bewirkt eine sofortige Erstberechnung und gibt ein Bestätigungsereignis aus, was für initiale Wertsetzungen oder Reset-Abläufe nützlich ist.
- **Wiederverwendung**: Intern kommt der IEC-61131-3-Funktionsblock `F_NOT_BOOL` zum Einsatz, der eine einfache Negation auf booleschen Werten realisiert.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten – er reagiert ereignisgesteuert. Vereinfachter Ablauf:

```
Ereignis (INIT oder IN.E1)
  → Erfasse IN.D1
  → Berechne NOT
  → Setze OUT.D1
  → Sende INITO und/oder OUT.E1
```

Der Baustein ist **nicht zustandsbehaftet**, d.h. jede neue Anforderung wird unabhängig von vorherigen Werten verarbeitet.

## Anwendungsszenarien

- **Signalnegation in modularen Systemen**: Wenn Ein- und Ausgänge über Adapter definiert sind, kann der Baustein als universeller NOT-Gatter eingesetzt werden, z.B. zur Invertierung von Aktor- oder Sensorwerten.
- **Initialisierungslogik**: Über den INIT-Eingang kann sichergestellt werden, dass der Ausgang beim Start einen definierten negierten Wert liefert.
- **Adapter-Kompatibilität**: In Systemen mit dem `AX`-Adapterprotokoll dient der Baustein als funktionaler Grundbaustein für logische Verknüpfungen.

## Vergleich mit ähnlichen Bausteinen

- **F_NOT_BOOL**: Standard IEC-61131-3 NOT-Funktion ohne Adapter. **AX_NOT_INIT** kapselt diese Funktionalität in eine Adapter-Schnittstelle und fügt ein INIT-Verhalten hinzu.
- **AX_AND / AX_OR**: Analoge Adapterbausteine für UND bzw. ODER. **AX_NOT_INIT** ist spezifisch für die Negation und besitzt nur einen Eingang.
- **F_TRIG / R_TRIG**: Flankenerkennung, die ebenfalls Ereignisse nutzt, aber keine logische Negation durchführt.

## Fazit

Der **AX_NOT_INIT**-Funktionsblock bietet eine effiziente und standardisierte Möglichkeit, boolesche Werte über den `AX`-Adapter zu negieren. Durch die Integration einer Initialisierungslogik eignet er sich besonders für Systeme, die beim Start einen definierten Ausgangszustand benötigen. Er ergänzt die Familie adapterbasierter Logikbausteine und vereinfacht die modulare Strukturierung von Automatisierungslösungen.