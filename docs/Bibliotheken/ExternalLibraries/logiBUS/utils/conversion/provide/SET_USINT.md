# SET_USINT


![SET_USINT](./SET_USINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **SET_USINT** dient dazu, einen über den Dateneingang **IN** bereitgestellten Wert vom Typ **USINT** direkt in die als InOut deklarierte Variable **OUT** zu schreiben. Der Baustein führt eine einfache Zuweisung aus und bestätigt die Ausführung durch das Ereignis **CNF**.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**  | Normaler Ausführungsanforderung – übernimmt den Wert von **IN** nach **OUT** und sendet **CNF**. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**  | Bestätigung der erfolgreichen Ausführung (wird nach der Zuweisung gesendet). |

### **Daten-Eingänge**

| Name | Datentyp | Initialwert | Beschreibung |
|------|----------|-------------|--------------|
| **IN** | USINT   | 0           | Wert, der in die Zielvariable geschrieben werden soll. |

### **Daten-Ausgänge**

| Name | Datentyp | Initialwert | Beschreibung |
|------|----------|-------------|--------------|
| **OUT** | USINT (InOut) | 0 | Zielvariable (als InOut deklariert, d. h. sie kann sowohl gelesen als auch geschrieben werden). Nach der Ausführung enthält **OUT** den Wert von **IN**. |

### **Adapter**

Keine.

## Funktionsweise

Wird das Ereignis **REQ** empfangen, führt der FB den Algorithmus **REQ** aus. Dieser weist den aktuellen Wert des Eingangs **IN** der InOut-Variable **OUT** zu (`OUT := IN;`). Anschließend wird das Ereignis **CNF** gesendet, um den Abschluss der Operation zu signalisieren. Der Baustein arbeitet ohne Verzögerung oder weitere Bedingungen.

## Technische Besonderheiten

- Die Verwendung einer **InOut**-Variable erlaubt es, **OUT** sowohl als Ziel (Ausgang) als auch als Quelle (Eingang) in anderen Bausteinen zu verwenden.
- Der Baustein ist auf den Datentyp **USINT** (8‑Bit vorzeichenloser Integer) festgelegt – eine direkte Konvertierung ist nicht vorgesehen.
- Es existiert nur ein einziger Zustand; der FB ist **ereignisgesteuert** und führt pro **REQ** genau eine Zuweisung aus.

## Zustandsübersicht

| Zustand | Aktion | Ausgangsereignis |
|---------|--------|------------------|
| **REQ** | Ausführen des Algorithmus **REQ** (`OUT := IN;`) | **CNF** |

Der FB besitzt keinen expliziten Startzustand – er wartet im Zustand **REQ** auf ein Ereignis.

## Anwendungsszenarien

- **Initialisierung** von Variablen oder Peripherie, die einen bestimmten USINT-Wert benötigen.
- **Parametrierung** von Geräten oder Funktionsbausteinen über eine InOut‑Variable.
- **Einfaches Setzen eines Wertes** in einer Steuerungslogik, wenn keine Berechnung oder Bedingung erforderlich ist.

## Vergleich mit ähnlichen Bausteinen

- **MOVE (ANY)**: Allgemeinerer Baustein zum Kopieren beliebiger Datentypen, oft ohne InOut-Fähigkeit.
- **SET_INT**, **SET_BYTE**, etc.: Analoge Bausteine für andere Integer-Typen – SET_USINT ist auf USINT spezialisiert.
- Im Gegensatz zu **LATCH** oder **SR‑Flipflops** speichert SET_USINT keinen Zustand, sondern führt eine einmalige Zuweisung durch.

## Fazit

**SET_USINT** ist ein minimalistischer und zuverlässiger Baustein zur direkten Wertzuweisung an eine InOut-Variable vom Typ USINT. Seine einfache Struktur eignet sich besonders für klare, sequenzielle Steuerungsaufgaben, bei denen ein Wert ohne Nebenwirkungen gesetzt werden muss.