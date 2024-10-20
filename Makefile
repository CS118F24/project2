# NOTE: Make sure you have your project files in the ./project directory
# Will run the autograder and place the results in ./results/results.json
IMAGE=reliability-is-essential

run:
	docker run --rm \
		-v ./project:/autograder/submission \
		-v ./results:/autograder/results \
		${IMAGE} \
		/autograder/run_autograder && cat results/results.json

# In case you want to run the autograder manually, use interactive
interactive:
	(docker ps | grep ${IMAGE} && \
	docker exec -it ${IMAGE} bash) || \
	docker run --rm --name ${IMAGE} -it \
		-v ./project:/autograder/submission \
		-v ./results:/autograder/results \
		${IMAGE} bash

build:
	docker build -t ${IMAGE} -f autograder/Dockerfile .

publish:
	docker tag ${IMAGE} eado0/${IMAGE}
	docker push eado0/${IMAGE}
