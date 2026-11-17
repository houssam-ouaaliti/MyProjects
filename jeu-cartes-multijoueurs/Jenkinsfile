pipeline {
    agent any

    stages {

        stage('Compilation') {
            steps {
                dir('1.Full-Stack-projects/jeu-cartes-multijoueur/backend') {
                    bat 'mvnw.cmd clean compile -q'
                }
            }
        }

        stage('Tests JUnit') {
            steps {
                dir('1.Full-Stack-projects/jeu-cartes-multijoueur/backend') {
                    bat 'mvnw.cmd test'
                }
            }
            post {
                always {
                    junit '1.Full-Stack-projects/jeu-cartes-multijoueur/backend/target/surefire-reports/*.xml'
                }
                failure {
                    echo 'Tests echoues — deploiement annule.'
                }
            }
        }

        stage('Package') {
            steps {
                dir('1.Full-Stack-projects/jeu-cartes-multijoueur/backend') {
                    bat 'mvnw.cmd package -DskipTests -q'
                }
            }
        }

        stage('Build Docker') {
            steps {
                dir('1.Full-Stack-projects/jeu-cartes-multijoueur') {
                    bat 'docker-compose build'
                }
            }
        }

        stage('Deploiement') {
            steps {
                dir('1.Full-Stack-projects/jeu-cartes-multijoueur') {
                    bat 'docker-compose down'
                    bat 'docker-compose up -d'
                }
                echo 'Application disponible sur http://localhost:5173'
            }
        }
    }

    post {
        success { echo 'Pipeline reussi.' }
        failure { echo 'Pipeline echoue — voir les logs.' }
    }
}